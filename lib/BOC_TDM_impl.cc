/* -*- c++ -*- */
/*
 * Copyright 2024 SEU tang.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "BOC_TDM_impl.h"
#include <gnuradio/io_signature.h>

namespace gr::jammingSource {

using output_type = gr_complex;
using in_type = gr_complex;
BOC_TDM::sptr BOC_TDM::make(float sample_freq, float period, float proportion)
{
    return gnuradio::make_block_sptr<BOC_TDM_impl>(sample_freq, period,proportion);
}


/*
 * The private constructor
 */
BOC_TDM_impl::BOC_TDM_impl(float sample_freq, float period, float proportion)
    : gr::sync_block("BOC_TDM",
                     gr::io_signature::make(2, 2, sizeof(in_type)),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)))
{
    current_count_ = 0;
    sample_freq_ = sample_freq;
    period_ = period;
    proportion_ = proportion;
    loop_sample_ = std::floor(period_ * sample_freq_);
    loop_sample_mainlobe_ = static_cast<int>(std::floor(period_ * sample_freq_ * (proportion_ / (proportion_ + 1))));
    loop_sample_sidelobe_ = loop_sample_ - loop_sample_mainlobe_;

    std::cout << "period = " <<period_<<std::endl;
    std::cout << "proportion = " <<proportion_<<std::endl;
    std::cout << "sample = " <<loop_sample_<<std::endl;
    std::cout << "sample mainlobe = " <<loop_sample_mainlobe_<<std::endl;
    std::cout << "sample sidelobe = " <<loop_sample_sidelobe_<<std::endl;
}

int BOC_TDM_impl::work(int noutput_items,
                       gr_vector_const_void_star& input_items,
                       gr_vector_void_star& output_items)
{
    gr::thread::scoped_lock l(this->d_setlock);
    auto out = static_cast<output_type*>(output_items[0]);
    auto in1 = static_cast<const in_type *>(input_items[0]);
    auto in2 = static_cast<const in_type *>(input_items[1]);

    int count = 0;
    while (count < noutput_items){
        if (current_count_ <= loop_sample_mainlobe_)
            *out++ = *in1++;
        else if (current_count_ > loop_sample_mainlobe_ && current_count_ < loop_sample_)
            *out++ = *in2++;
        else
        {
            current_count_ = 1;
            continue;
        }
        count++;
        current_count_++;
    }
    return noutput_items;
}
void BOC_TDM_impl::set_sampling_freq(float samp_rate) {
    this->sample_freq_ = samp_rate;
}
void BOC_TDM_impl::set_period(float period) {
    this->period_ = period;
}
void BOC_TDM_impl::set_proportion(float proportion) {
    this->proportion_ = proportion;
}

} // namespace gr::jammingSource

