//    AdiosStMan.cc: Storage Manager for general CASA tables using ADIOS
//    as the underlying IO & storage library
//
//    (c) University of Western Australia
//    International Centre of Radio Astronomy Research
//    M468, 35 Stirling Hwy
//    Crawley, Perth WA 6009
//    Australia
//
//    This library is free software: you can redistribute it and/or
//    modify it under the terms of the GNU General Public License as published
//    by the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License along
//    with this library. If not, see <http://www.gnu.org/licenses/>.
//
//    Any bugs, questions, concerns and/or suggestions please email to
//    jason.wang@icrar.org

#include "AdiosStManIndColumn.h"
#include "AdiosStManDirColumn.h"
#include "AdiosStManScaColumn.h"


namespace casacore {

    int AdiosStMan::itsNrInstances = 0;

    AdiosStMan::AdiosStMan(string aMethod, string aPara, uint64_t writeBufsize, uint64_t readBufsize)
        :DataManager(),
        itsDataManName("AdiosStMan"),
        itsAdiosWriteFile(0),
        itsAdiosReadFile(0),
        itsNrAdiosFiles(0),
        itsMpiComm(MPI_COMM_WORLD),
        itsAdiosTransMethod(aMethod),
        itsAdiosTransPara(aPara),
        itsAdiosWriteBufsize(writeBufsize),
        itsAdiosReadBufsize(readBufsize),
        isMpiInitInternal(false)
    {
        AdiosStMan::itsNrInstances++;
        int isMpiInitialized;
        MPI_Initialized(&isMpiInitialized);
        if(!isMpiInitialized){
            MPI_Init(0,0);
            isMpiInitInternal = true;
        }
        MPI_Initialized(&isMpiInitialized);
        MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
        MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
    }

    AdiosStMan::AdiosStMan (const AdiosStMan& that)
        :DataManager(),
        itsDataManName(that.itsDataManName),
        itsAdiosWriteFile(that.itsAdiosWriteFile),
        itsAdiosReadFile(that.itsAdiosReadFile),
        itsNrAdiosFiles(that.itsNrAdiosFiles),
        itsMpiComm(MPI_COMM_WORLD),
        itsStManColumnType(that.itsStManColumnType),
        itsAdiosTransMethod(that.itsAdiosTransMethod),
        itsAdiosTransPara(that.itsAdiosTransPara),
        itsAdiosWriteBufsize(that.itsAdiosWriteBufsize),
        itsAdiosReadBufsize(that.itsAdiosReadBufsize),
        isMpiInitInternal(false)
    {
        AdiosStMan::itsNrInstances++;
        MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
        MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);
    }

    DataManager* AdiosStMan::makeObject (const casa::String& aDataManType, const casa::Record& spec){
        return new AdiosStMan();
    }

    AdiosStMan::~AdiosStMan ()
    {
        AdiosStMan::itsNrInstances--;
        adios_finalize(mpiRank);
        if(itsAdiosReadFile){
            adios_read_close(itsAdiosReadFile);
            MPI_Barrier(MPI_COMM_WORLD);
            adios_read_finalize_method(ADIOS_READ_METHOD_BP);
        }
        int isMpiInitialized;
        MPI_Initialized(&isMpiInitialized);
        if(isMpiInitInternal && isMpiInitialized){
            if(AdiosStMan::itsNrInstances==0)
                // Some python-casacore code instantiates storage managers multiple times in a run,
                // while MPI standard does not allow calling anything MPI after MPI_Finalize() is called,
                // even another MPI_Init() is not allowed, otherwise there will be an error.
                // So this is currently the only way to avoid that -- only call MPI_Finalize when
                // 1, there are multiple MPI ranks existing;
                // 2, this is the last existing AdiosStMan instance;
                // 3, MPI_Init was called inside AdiosStMan
                if(mpiSize > 1)
                    MPI_Finalize();
        }
    }

    void AdiosStMan::logdbg(string func, string stat, int para){
#ifdef ADIOSSTMAN_DEBUG
        if(logdbgLast == func){
            logdbgCount++;
        }
        else{
            logdbgCount=0;
        }
        cout << func << " called, count=" << logdbgCount << ".";
        cout << stat << para << endl;
        logdbgLast=func;
#endif
    }

    DataManager* AdiosStMan::clone() const
    {
        return new AdiosStMan (*this);
    }

    String AdiosStMan::dataManagerType() const
    {
        return itsDataManName;
    }

    int64_t AdiosStMan::getAdiosGroup(){
        return itsAdiosGroup;
    }

    int64_t AdiosStMan::getAdiosFile(){
        return itsAdiosWriteFile;
    }

    ADIOS_FILE* AdiosStMan::getAdiosReadFile(){
        return itsAdiosReadFile;
    }

    void AdiosStMan::addRow (uInt aNrRows){
        cout << "AdiosStMan Error: addRow not supported!" << endl;
    }

    void AdiosStMan::adiosWriteOpen(){
        if(!itsAdiosWriteFile){
            logdbg("AdiosStMan::adiosWriteOpen","");
            // broadcast the filename string from the master to slaves.
            string itsFileName;
            int itsFileNameLen;
            if(mpiRank == 0){
                itsFileName = fileName();
                itsFileNameLen = itsFileName.length();
            }
            MPI_Bcast(&itsFileNameLen, 1, MPI_INT, 0, itsMpiComm);
            char *itsFileNameChar = new char [itsFileNameLen + 1];
            sprintf(itsFileNameChar,"%s", itsFileName.c_str());
            MPI_Bcast(itsFileNameChar, itsFileNameLen + 1, MPI_CHAR, 0, itsMpiComm);
            // create ADIOS file
            adios_init_noxml(itsMpiComm);
            adios_allocate_buffer(ADIOS_BUFFER_ALLOC_NOW, itsAdiosWriteBufsize);
            adios_declare_group(&itsAdiosGroup, "casatable", "", adios_flag_no);
            adios_select_method(itsAdiosGroup, itsAdiosTransMethod.c_str(), itsAdiosTransPara.c_str(), "");
            for (uInt i=0; i<itsNrCols; i++){
                itsColumnPtrBlk[i]->initAdiosWrite(itsNrRows);
            }
            itsAdiosGroupsize = 0;
            for (uInt i=0; i<itsNrCols; i++){
                // if scalar column
                if (itsColumnPtrBlk[i]->getShapeColumn().nelements() == 0){
                    itsAdiosGroupsize = itsAdiosGroupsize + itsNrRows * itsColumnPtrBlk[i]->getDataTypeSize();
                }
                // if array column
                else{
                    itsAdiosGroupsize = itsAdiosGroupsize + itsNrRows * itsColumnPtrBlk[i]->getDataTypeSize() * itsColumnPtrBlk[i]->getShapeColumn().product();
                }
            }
            adios_open(&itsAdiosWriteFile, "casatable", itsFileNameChar, "w", itsMpiComm);
            adios_group_size(itsAdiosWriteFile, itsAdiosGroupsize, &itsAdiosTotalsize);
            delete [] itsFileNameChar;
        }
    }

    void AdiosStMan::adiosWriteClose(){
        if(itsAdiosWriteFile){
            adios_close(itsAdiosWriteFile);
            itsAdiosWriteFile = 0;
        }
    }

    void AdiosStMan::create (uInt aNrRows){
        logdbg("AdiosStMan::create","");
        itsMode = 'w';
        itsNrRows = aNrRows;
        itsNrCols = ncolumn();
        MPI_Bcast(&itsNrCols, 1, MPI_UNSIGNED, 0, itsMpiComm);
        MPI_Bcast(&itsNrRows, 1, MPI_UNSIGNED, 0, itsMpiComm);
    } // end of void AdiosStMan::create (uInt aNrRows)

    void AdiosStMan::open (uInt aNrRows, AipsIO& ios){
        logdbg("AdiosStMan::open","");
        ios.getstart(itsDataManName);
        ios >> itsDataManName;
        ios >> itsStManColumnType;
        ios.getend();
        itsMode = 'r';
        itsNrRows = aNrRows;
        adios_read_init_method (ADIOS_READ_METHOD_BP, MPI_COMM_WORLD, "verbose=3");
        itsAdiosReadFile = adios_read_open (fileName().c_str(), ADIOS_READ_METHOD_BP, MPI_COMM_WORLD, ADIOS_LOCKMODE_NONE, 0);
        if(itsAdiosReadFile){
            for (int i=0; i<ncolumn(); i++){
                itsColumnPtrBlk[i]->initAdiosRead();
            }
        }
    }

    void AdiosStMan::deleteManager(){
    }

    DataManagerColumn* AdiosStMan::makeScalarColumn (const String& name, int aDataType, const String& dataTypeId){
        logdbg("AdiosStMan::makeScalarColumn","");
        return makeColumnMeta(name, aDataType, dataTypeId, 's');
    }

    DataManagerColumn* AdiosStMan::makeDirArrColumn (const String& name, int aDataType, const String& dataTypeId){
        logdbg("AdiosStMan::makeDirArrColumn","");
        return makeColumnMeta(name, aDataType, dataTypeId, 'd');
    }

    DataManagerColumn* AdiosStMan::makeIndArrColumn (const String& name, int aDataType, const String& dataTypeId){
        logdbg("AdiosStMan::makeIndArrColumn","");
#ifdef ADIOSSTMAN_FORCE_DIRECT_ARRAY
        return makeColumnMeta(name, aDataType, dataTypeId, 'd');
#else
        return makeColumnMeta(name, aDataType, dataTypeId, 'i');
#endif
    }

    DataManagerColumn* AdiosStMan::makeColumnMeta (const String& name, int aDataType, const String& dataTypeId, char columnType){
        if (ncolumn() >= itsColumnPtrBlk.nelements()) {
            itsColumnPtrBlk.resize (itsColumnPtrBlk.nelements() + 32);
        }
        AdiosStManColumn* aColumn;
        switch (columnType){
            case 's':
                aColumn = new AdiosStManScaColumn (this, aDataType, ncolumn());
                break;
            case 'd':
                aColumn = new AdiosStManDirColumn (this, aDataType, ncolumn());
                break;
            case 'i':
                aColumn = new AdiosStManIndColumn (this, aDataType, ncolumn());
                break;
        }
        aColumn->setColumnName(name);
        itsColumnPtrBlk[ncolumn()] = aColumn;
        return aColumn;
    }

    uInt AdiosStMan::getNrRows(){
        return itsNrRows;
    }

    void AdiosStMan::resync (uInt aNrRows){
    }

    Bool AdiosStMan::flush (AipsIO& ios, Bool doFsync){
        for (int i=0; i<ncolumn(); i++){
            itsColumnPtrBlk[i]->flush();
        }
        ios.putstart(itsDataManName, 2);
        ios << itsDataManName;
        ios << itsStManColumnType;
        ios.putend();
        adiosWriteClose();
        return true;
    }

    char AdiosStMan::getMode (){
        return itsMode;
    }

    uint64_t AdiosStMan::getReadBufsize (){
        return itsAdiosReadBufsize;
    }

    String AdiosStMan::dataManagerName() const
    {
        return itsDataManName;
    }
    void register_adiosstman(){
        DataManager::registerCtor ("AdiosStMan", AdiosStMan::makeObject);
    }
}

