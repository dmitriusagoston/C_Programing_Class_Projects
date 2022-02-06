#include "mathlib.h"

#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OPTIONS "aebmrvnsh:"
#define m_pi    3.141592653589793
#define m_e     2.718281828459045

int main(int argc, char **argv) {
    int c = 0;
    // bools for each command option
    bool a = false;
    bool E = false;
    bool b = false;
    bool m = false;
    bool r = false;
    bool v = false;
    bool n = false;
    bool s = false;
    bool h = false;
    // parse command line
    while ((c = getopt(argc, argv, OPTIONS)) != -1) {
        // determine which tests to run
        if (c == 97) {
            a = true;
        }
        if (c == 101) {
            E = true;
        }
        if (c == 98) {
            b = true;
        }
        if (c == 109) {
            m = true;
        }
        if (c == 114) {
            r = true;
        }
        if (c == 118) {
            v = true;
        }
        if (c == 110) {
            n = true;
        }
        // statistics on or off used at bottom of each test
        if (c == 115) {
            s = true;
        }
    }
    // check for help print
    if (a != true && E != true && b != true && m != true && r != true && v != true && n != true) {
        h = true;
    }
    // check for all
    if (a == true) {
        E = true;
        b = true;
        m = true;
        r = true;
        v = true;
        n = true;
    }
    // check for e
    if (E == true) {
        printf("e() = %16.15f, ", e());
        printf("M_E = %16.15f, ", m_e);
        printf("diff = %16.15f\n", absolute(e() - m_e));
        if (s) {
            printf("e() terms = %d\n", e_terms() / 2);
        }
    }
    // check for bbp
    if (b == true) {
        printf("pi_bbp() = %16.15f, ", pi_bbp());
        printf("M_PI = %16.15f, ", m_pi);
        printf("diff = %16.15f\n", absolute(pi_bbp() - m_pi));
        if (s) {
            printf("pi_bbp() terms = %d\n", pi_bbp_terms() / 2);
        }
    }
    // check for madhava
    if (m == true) {
        printf("pi_madhava() = %16.15f, ", pi_madhava());
        printf("M_PI = %16.15f, ", m_pi);
        printf("diff = %16.15f\n", absolute(pi_madhava() - m_pi));
        if (s) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms() / 2);
        }
    }
    // check for euler
    if (r == true) {
        printf("pi_euler() = %16.15f, ", pi_euler());
        printf("M_PI = %16.15f, ", m_pi);
        printf("diff = %16.15f\n", absolute(pi_euler() - m_pi));
        if (s) {
            printf("pi_euler() terms = %d\n", pi_euler_terms() / 2);
        }
    }
    // check for viete
    if (v == true) {
        printf("pi_viete() = %16.15f, ", pi_viete());
        printf("M_PI = %16.15f, ", m_pi);
        printf("diff = %16.15f\n", absolute(pi_viete() - m_pi));
        if (s) {
            printf("pi_viete() terms = %d\n", pi_viete_factors() / 2);
        }
    }
    // check for square root
    if (n == true) {
        for (double i = 0.0; i < 10.0; i += 0.1) {
            printf("sqrt_newton(%2.6f) = %16.15f, ", i, sqrt_newton(i));
            printf("sqrt(%2.6f) = %16.15f, ", i, sqrt(i));
            printf("diff = %16.15f\n", absolute(sqrt_newton(i) - sqrt(i)));
            if (s == true) {
                // divide by 2 for double call
                printf("sqrt_newton() terms = %d\n", sqrt_newton_iters() / 2);
            }
        }
    }
    // help print
    if (h == true) {
        printf("SYNOPSIS\n");
        printf("    A test harness for the small numerical library.\n\n");
        printf("USAGE\n");
        printf("    ./mathlib-test [-aebmrvnsh]\n\n");
        printf("OPTIONS\n");
        printf("-a   Runs all tests.\n");
        printf("-e   Runs e test.\n");
        printf("-b   Runs BBP pi test.\n");
        printf("-m   Runs Madhava pi test.\n");
        printf("-r   Runs Euler pi test.\n");
        printf("-v   Runs Viete pi test.\n");
        printf("-n   Runs Newton square root tests.\n");
        printf("-s   Print verbose statistics.\n");
        printf("-h   Display program synopsis and usage.\n");
    }
    return 0;
}
