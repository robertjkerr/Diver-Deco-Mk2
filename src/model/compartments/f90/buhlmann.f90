module buhlmann
    use constants
    use iso_c_binding
    implicit NONE

    contains
    !**
    ! Invokes Buhlmann dive segment on tissues
    !**
    subroutine buhl_segment(pressures_both, gas, start_depth, depth_rate, time)
        implicit NONE

        REAL, DIMENSION(2, num_comps), INTENT(INOUT) :: pressures_both
        REAL, DIMENSION(2), INTENT(IN) :: gas !Should be {fN2, fHe}
        INTEGER, INTENT(IN) :: start_depth, depth_rate, time

        REAL, DIMENSION(2,num_comps) :: k_vals_both
        REAL :: p_amb, p_amb_N2, p_amb_He, p_rate, p_rate_N2, p_rate_He

        k_vals_both(1,:) = LOG(2.0) / (halfLivesN2*60)
        k_vals_both(2,:) = LOG(2.0) / (halfLivesHe*60)

        p_amb = REAL(start_depth)/10 + 1
        p_amb_N2 = p_amb * gas(1)
        p_amb_He = p_amb * gas(2)

        p_rate = depth_rate/10
        p_rate_N2 = p_rate * gas(1)
        p_rate_He = p_rate * gas(2)

        pressures_both(1,:) = SCHREINER(k_vals_both(1,:), pressures_both(1,:), &
                                p_rate_N2, p_amb_N2, time)
        pressures_both(2,:) = SCHREINER(k_vals_both(2,:), pressures_both(2,:), &
                                p_rate_He, p_amb_He, time) 

    end subroutine buhl_segment


    !**
    ! Method behind BUHL_SEGMENT - vectorisation of Schreiner equation
    !**
    function SCHREINER(k_vals, pressures, p_rate, p_amb_gas, time)
        implicit NONE

        REAL, DIMENSION(:), INTENT(IN) :: k_vals, pressures
        REAL, INTENT(IN) :: p_rate, p_amb_gas
        INTEGER, INTENT(IN) :: time
        REAL, DIMENSION(SIZE(pressures)) :: SCHREINER

        REAL, DIMENSION(SIZE(k_vals)) :: expkt

        expkt = EXP(-k_vals * time)

        SCHREINER = p_amb_gas*(1 - expkt) + &
                    p_rate*(time - 1/k_vals + expkt/k_vals) + &
                    pressures * expkt

    end function SCHREINER


    !**
    ! Returns the ceiling of the tissues
    !**
    INTEGER function depth_ceiling(pressures_both, GF)
        implicit NONE

        REAL, DIMENSION(2, num_comps), INTENT(IN) :: pressures_both
        REAL, INTENT(IN) :: GF

        REAL, DIMENSION(num_comps) :: A_vals, B_vals, p_ceil_vals, p_sum
        REAL :: p_ceil       

        p_sum = pressures_both(1,:) + pressures_both(2,:)

        A_vals =  (AValsN2 * pressures_both(1,:) + &
                AValsHe * pressures_both(2,:))/ p_sum
                
        B_vals = (BValsN2 * pressures_both(1,:) + &
                BValsHe * pressures_both(2,:))/ p_sum

        p_ceil_vals = (p_sum - GF * A_vals) * &
                B_vals / (B_vals + GF*(1 - B_vals)) 

        p_ceil = MAXVAL(p_ceil_vals)
        depth_ceiling = (INT(p_ceil) - 1) * 10

    end function depth_ceiling

end module buhlmann