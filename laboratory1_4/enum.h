
#ifndef LABORATORY1_4_ENUM_H
#define LABORATORY1_4_ENUM_H

enum input_status_code {
    isc_need_help,
    isc_bad_input,
    isc_d,
    isc_i,
    isc_s,
    isc_a,
    isc_nd,
    isc_ni,
    isc_ns,
    isc_na
};

enum is_open_file_read {
    iofr_not,
    iofr_yes
};

enum is_open_file_write {
    iofw_not,
    iofw_yes
};

enum input_n{
    in_yes,
    in_not,
    in_wrong_num
};

#endif //LABORATORY1_4_ENUM_H
