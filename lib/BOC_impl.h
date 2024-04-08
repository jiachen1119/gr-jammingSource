/* -*- c++ -*- */
/*
 * Copyright 2024 SEU tang.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_JAMMINGSOURCE_BOC_IMPL_H
#define INCLUDED_JAMMINGSOURCE_BOC_IMPL_H

#include <gnuradio/analog/sig_source.h>
#include <gnuradio/analog/sig_source_waveform.h>
#include <gnuradio/jammingSource/BOC.h>
#include <gnuradio/random.h>

namespace gr::jammingSource {

class BOC_impl : public BOC
{
private:
    // modulation coefficient
    int n_;
    // the chip rate of the pseudocode
    float RC_;
    // the chip rate of the sub-carrier
    float Rs_;
    float chips_per_sample_;
    float sample_freq_;
    gr::random d_rng;

    int current_sample_count_ = 0;
    int current_value_ = 1;
    float rem_chip_ = 0;
    int current_subcarrier_value = 1;

public:
    BOC_impl(int a, int b, float samp_freq);
    ~BOC_impl() override = default;

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override;

    double sampling_freq()const override {return sample_freq_;}
    void set_sampling_freq(float samp_rate) override;


};

} // namespace gr::jammingSource


#endif /* INCLUDED_JAMMINGSOURCE_BOC_IMPL_H */
