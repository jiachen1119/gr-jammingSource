/* -*- c++ -*- */
/*
 * Copyright 2024 SEU tang.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_JAMMINGSOURCE_BOC_TDM_IMPL_H
#define INCLUDED_JAMMINGSOURCE_BOC_TDM_IMPL_H

#include <gnuradio/jammingSource/BOC_TDM.h>
#include <gnuradio/random.h>

namespace gr::jammingSource {

class BOC_TDM_impl : public BOC_TDM
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
    float period_;
    gr::random d_rng;

    int current_sample_count_ = 0;
    int current_value_ = 1;
    float rem_chip_ = 0;
    int current_subcarrier_value = 1;

public:
    BOC_TDM_impl(int a, int b, float sample_freq, float period);
    ~BOC_TDM_impl() override = default;

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override;

    float sampling_freq()const override {return sample_freq_;}
    void set_sampling_freq(float samp_rate) override;

    float period()const override {return period_;}
    void set_period(float period) override;
};

} // namespace gr::jammingSource


#endif /* INCLUDED_JAMMINGSOURCE_BOC_TDM_IMPL_H */
