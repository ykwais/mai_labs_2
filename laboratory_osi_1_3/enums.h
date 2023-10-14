
#ifndef LABORATORY_OSI_1_3_ENUMS_H
#define LABORATORY_OSI_1_3_ENUMS_H

enum input_status_code{
    isc_well,
    isc_bad_input
};

typedef enum input_status_code input_code;

enum troubles_file{
    tf_well,
    tf_input_trouble,
    tf_output_trouble,
    tf_not_the_same
};

typedef enum troubles_file problems_file;

#endif //LABORATORY_OSI_1_3_ENUMS_H
