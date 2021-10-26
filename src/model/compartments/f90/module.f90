module fortran_interface
    use buhlmann, ONLY: buhl_segment, depth_ceiling
    use constants
    use iso_c_binding
    implicit NONE
    contains

    subroutine invoke_buhl_seg(pressures_both, gas, &
                        start_depth, depth_rate, time) bind(C)
        implicit NONE

        REAL (c_float), DIMENSION(2,num_comps), INTENT(INOUT) :: pressures_both
        REAL (c_float), DIMENSION(2), INTENT(IN) :: gas
        INTEGER (c_int16_t), INTENT(IN) :: start_depth, time
        INTEGER (c_int8_t), INTENT(IN) :: depth_rate

        CALL buhl_segment(pressures_both, gas, INT(start_depth), INT(depth_rate), INT(time))

    end subroutine invoke_buhl_seg


    INTEGER (c_int16_t) function get_ceiling(pressures_both, GF) bind(C)
        implicit NONE

        REAL (c_float), INTENT(IN) :: GF
        REAL (c_float), DIMENSION(2, num_comps), INTENT(IN) :: pressures_both

        get_ceiling = INT2(depth_ceiling(REAL(pressures_both), REAL(GF)))

    end function get_ceiling

end module fortran_interface
    