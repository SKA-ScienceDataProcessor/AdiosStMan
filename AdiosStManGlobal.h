// casacore version, CASACORE_VERSION_1 or CASACORE_VERSION_2
#define CASACORE_VERSION_2

// whether to print out debug info
//#define ADIOSSTMAN_DEBUG

// whether to force AdiosStMan treat any array columns as direct array columns while writing
// This could cause problems if any array column has different array shapes across different rows
// But for most measurement set tables with DATA columns made using TableDesc::Undefined but actually contain pre-defined shaped data arrays, this performs much better
#define ADIOSSTMAN_FORCE_DIRECT_ARRAY



