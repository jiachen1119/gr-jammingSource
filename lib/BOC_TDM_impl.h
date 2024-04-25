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
#include <gnuradio/filter/firdes.h>
#include <gnuradio/filter/fft_filter_fff.h>

namespace gr::jammingSource {

class BOC_TDM_impl : public BOC_TDM
{
private:
    float sample_freq_;
    float period_;
    float proportion_;

    int loop_sample_mainlobe_;
    int loop_sample_sidelobe_;
    int current_count_;
    int loop_sample_;

public:
    BOC_TDM_impl(float sample_freq, float period, float proportion);
    ~BOC_TDM_impl() override = default;

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override;

    float sampling_freq()const override {return sample_freq_;}
    void set_sampling_freq(float samp_rate) override;

    float period()const override {return period_;}
    void set_period(float period) override;

    float proportion()const override{return proportion_;}
    void set_proportion(float proportion) override;
};

} // namespace gr::jammingSource


#endif /* INCLUDED_JAMMINGSOURCE_BOC_TDM_IMPL_H */
