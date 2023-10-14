
#ifndef LABORATORY_OSI_1_4_ENUMS_H
#define LABORATORY_OSI_1_4_ENUMS_H

enum open_file_problem {
    ofp_well,
    ofp_bad_open
};

typedef enum open_file_problem file_troubles;

enum input_status_code {
    isc_too_args,
    isc_xor8,
    isc_xor32,
    isc_mask,
    isc_bad_input
};

typedef enum input_status_code input;

enum memory_troubles{
    mt_well,
    mt_memory_problem
};

typedef enum memory_troubles memory;

enum valid_value_mask{
    vvm_valid,
    vvm_invalid
};

typedef enum valid_value_mask valid_mask;

#endif //LABORATORY_OSI_1_4_ENUMS_H
