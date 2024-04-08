/* -*- c++ -*- */
/*
 * Copyright 2024 SEU tang.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "BOC_impl.h"
#include <gnuradio/io_signature.h>

namespace gr::jammingSource {

using output_type = float;
BOC::sptr BOC::make(int a,int b, float samp_freq) { return gnuradio::make_block_sptr<BOC_impl>(a,b,samp_freq); }


/*
 * The private constructor
 */
BOC_impl::BOC_impl(int a,int b,float samp_freq)
    : gr::sync_block("BOC",
                     gr::io_signature::make(0, 0, 0),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)))
{
    n_ = static_cast<int>((static_cast<float>(a) / static_cast<float>(b)) * 2);
    sample_freq_ = samp_freq;
    RC_ = static_cast<float> (b * 1.023e6);
    Rs_ = static_cast<float> (a * 1.023e6);
    chips_per_sample_ = (2 * Rs_)/ sample_freq_ ;
    d_rng.set_integer_limits(0,2);
    d_rng.reseed(1);
    current_sample_count_ = 0;
    current_value_ = 1;
    current_subcarrier_value *= current_value_;
    rem_chip_ = 0;
    std::cout << "a = " <<a<<" b = "<<b<<" sampling frequency = "<<sample_freq_<<std::endl;
    std::cout << "chips per sample = " << chips_per_sample_ <<std::endl;
}

int BOC_impl::work(int noutput_items,
                   gr_vector_const_void_star& input_items,
                   gr_vector_void_star& output_items)
{
    auto out = static_cast<output_type*>(output_items[0]);
    int count = 0;
    while(count < noutput_items)
    {
        if (std::floor(current_sample_count_ * chips_per_sample_ + rem_chip_) >= n_){
            // produce a random number
            int temp = static_cast<int>(d_rng.ran_int());
            if(temp == 0) current_value_ = -1;
            else current_value_ = 1;
            // record the remnant chip
            rem_chip_ = current_sample_count_ * chips_per_sample_ - n_;
            current_sample_count_ = 0;
        }
        if ((int)std::floor(current_sample_count_ * chips_per_sample_ + rem_chip_) !=
            (int)std::floor((current_sample_count_-1) * chips_per_sample_ + rem_chip_))
            current_subcarrier_value = -current_subcarrier_value;
        *out = static_cast<output_type>(current_subcarrier_value * current_value_);
        out++;
        current_sample_count_++;
        count++;
    }
    // Tell runtime system how many output items we produced.
    return noutput_items;
}
void BOC_impl::set_sampling_freq(float samp_rate) {
    this->sample_freq_ = samp_rate;
    this->chips_per_sample_ = sample_freq_ / Rs_;
}


} // namespace gr::jammingSource

