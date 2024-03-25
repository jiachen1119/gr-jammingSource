//
// Created by tang on 24-3-24.
//

#ifndef GR_JAMMINGSOURCE_CUSTOMNCO_H
#define GR_JAMMINGSOURCE_CUSTOMNCO_H

#include <gnuradio/api.h>
#include <gnuradio/gr_complex.h>
#include <cstdint>

namespace gr {

/*!
 * \brief Numerically Controlled Oscillator (NCO)
 * \ingroup misc
 */
class CustomNco
{
    float d_phase;
    float d_phase_inc;

public:
    CustomNco() : d_phase(0), d_phase_inc(0) {}

    ~CustomNco() {}

    // radians
    void set_phase(float angle) { d_phase = angle; }

    void adjust_phase(float delta_phase)
    {
        d_phase += delta_phase;
    }

    // angle_rate is in radians / step
    void set_freq(float angle_rate)
    {
        d_phase_inc = angle_rate;
    }

    // angle_rate is a delta in radians / step
    void adjust_freq(float delta_angle_rate)
    {
        d_phase_inc += delta_angle_rate;
    }

    // increment current phase angle

    void step() { d_phase += d_phase_inc; }

    void step(int n) { d_phase += d_phase_inc * n; }

    // units are radians / step
    float get_phase() const { return d_phase; }
    float get_freq() const { return d_phase_inc; }

    // compute sin and cos for current phase angle
    void sincos(float * sinx, float * cosx) const
    {
        *sinx = std::sin(d_phase);
        *cosx = std::cos(d_phase);
    }

    // compute cos and sin for a block of phase angles
    void sincos(gr_complex* output, int noutput_items, double ampl = 1.0)
    {
        for (int i = 0; i < noutput_items; i++) {
            output[i] =
                gr_complex(std::cos(d_phase) * ampl, std::sin(d_phase) * ampl);
            step();
        }
    }

    // compute sin for a block of phase angles
    void sin(float* output, int noutput_items, double ampl = 1.0)
    {
        for (int i = 0; i < noutput_items; i++) {
            output[i] = (float)(std::sin(d_phase) * ampl);
            step();
        }
    }

    // compute cos for a block of phase angles
    void cos(float* output, int noutput_items, double ampl = 1.0)
    {
        for (int i = 0; i < noutput_items; i++) {
            output[i] = (float)(std::cos(d_phase) * ampl);
            step();
        }
    }

    // compute sin for a block of phase angles
    void sin(std::int8_t* output, int noutput_items, double ampl = 1.0)
    {
        for (int i = 0; i < noutput_items; i++) {
            output[i] = (std::int8_t)(std::sin(d_phase) * ampl);
            step();
        }
    }

    // compute cos for a block of phase angles
    void cos(std::int8_t* output, int noutput_items, double ampl = 1.0)
    {
        for (int i = 0; i < noutput_items; i++) {
            output[i] = (std::int8_t)(std::cos(d_phase) * ampl);
            step();
        }
    }

    // compute sin for a block of phase angles
    void sin(short* output, int noutput_items, double ampl = 1.0)
    {
        for (int i = 0; i < noutput_items; i++) {
            output[i] = (short)(std::sin(d_phase) * ampl);
            step();
        }
    }

    // compute cos for a block of phase angles
    void cos(short* output, int noutput_items, double ampl = 1.0)
    {
        for (int i = 0; i < noutput_items; i++) {
            output[i] = (short)(std::cos(d_phase) * ampl);
            step();
        }
    }

    // compute sin for a block of phase angles
    void sin(int* output, int noutput_items, double ampl = 1.0)
    {
        for (int i = 0; i < noutput_items; i++) {
            output[i] = (int)(std::sin(d_phase) * ampl);
            step();
        }
    }

    // compute cos for a block of phase angles
    void cos(int* output, int noutput_items, double ampl = 1.0)
    {
        for (int i = 0; i < noutput_items; i++) {
            output[i] = (int)(std::cos(d_phase) * ampl);
            step();
        }
    }

    // compute cos or sin for current phase angle
    float cos() const { return std::cos(d_phase); }
    float sin() const { return std::sin(d_phase); }
};

} /* namespace gr */

#endif // GR_JAMMINGSOURCE_CUSTOMNCO_H
