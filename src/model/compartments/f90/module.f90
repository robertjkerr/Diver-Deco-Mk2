module fortran_interface
    use buhlmann
    use constants
    use iso_c_binding
    implicit NONE
    contains

    subroutine invoke_dive_segment_buhl(pressures_both, gas, &
                        start_depth, depth_rate, time) bind(C)
        implicit NONE

        REAL (c_float), DIMENSION(num_comps,2), INTENT(INOUT) :: pressures_both
        REAL (c_float), DIMENSION(2), INTENT(IN) :: gas
        INTEGER (c_int16_t), INTENT(IN) :: start_depth, time
        INTEGER (c_int8_t), INTENT(IN) :: depth_rate
        REAL, DIMENSION(2, num_comps) :: in_pres

        in_pres = TRANSPOSE(pressures_both)
        pressures_both = TRANSPOSE(buhl_segment(in_pres, gas, INT(start_depth), INT(depth_rate), INT(time)))

    end subroutine invoke_dive_segment_buhl


    INTEGER (c_int16_t) function get_ceiling(pressures_both, GF) bind(C)
        implicit NONE

        REAL (c_float), INTENT(IN) :: GF
        REAL (c_float), DIMENSION(num_comps, 2), INTENT(IN) :: pressures_both
        REAL, DIMENSION(2, num_comps) :: in_pres

        in_pres = TRANSPOSE(pressures_both)
        get_ceiling = INT2(depth_ceiling(in_pres, REAL(GF)))

    end function get_ceiling

end module fortran_interface
    