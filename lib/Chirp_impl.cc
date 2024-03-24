/* -*- c++ -*- */
/*
 * Copyright 2022 mortarboard-H.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "Chirp_impl.h"
#include <gnuradio/io_signature.h>
#include <gnuradio/math.h>

namespace gr::jammingSource {

using output_type = gr_complex;
Chirp::sptr Chirp::make(double samp_rate, double min_freq, double max_freq, double period)
{
    return gnuradio::make_block_sptr<Chirp_impl>(samp_rate, min_freq, max_freq, period);
}


/*
 * The private constructor
 */
Chirp_impl::Chirp_impl(double samp_rate, double min_freq, double max_freq, double period)
    : gr::sync_block("Chirp",
                     gr::io_signature::make(0, 0, 0),
                     gr::io_signature::make(
                         1, 1, sizeof(output_type))),
      samplingFrequency_(samp_rate),
      period_(period),
      maxFrequency_(max_freq),
      minFrequency_(min_freq)
{
    this->reset_all();
}

Chirp_impl::~Chirp_impl() = default;

int Chirp_impl::work(int noutput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items)
{
    auto out = static_cast<output_type*>(output_items[0]);
    float sin_num,cos_num;

    for(int i = 0; i < noutput_items ; i++)
    {
        nco_.sincos(&cos_num,&sin_num);
        *out++= gr_complex(sin_num,cos_num);
        nco_.adjust_freq(2 * GR_M_PI * freqIncPerSample_ / samplingFrequency_);
        nco_.step();
        
        auto curfreq = nco_.get_freq();
        if(curfreq > 2 * GR_M_PI * maxFrequency_ / samplingFrequency_)
            nco_.set_freq(2 * GR_M_PI * minFrequency_ / samplingFrequency_);
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

void Chirp_impl::set_sampling_freq(double samp_rate)
{
    this->samplingFrequency_ = samp_rate;
    this->reset_all();
}

void Chirp_impl::set_period(double period)
{
    this->period_ = period;
    this->reset_all();
}

void Chirp_impl::set_min_freq(double min_freq)
{
    this->minFrequency_ = min_freq;
    this->reset_all();
}

void Chirp_impl::set_max_freq(double max_freq)
{
    this->maxFrequency_ = max_freq;
    this->reset_all();
}

void Chirp_impl::reset_all()
{
    // set d_samples per loop
    double samples_per_loop = period_ * samplingFrequency_;
    samplesPerLoop_ = (int) samples_per_loop;

    // set frequency increments per sample
    freqIncPerSample_ = (maxFrequency_ - minFrequency_) / (double)samplesPerLoop_;

    nco_.set_freq(2 * GR_M_PI * minFrequency_ / samplingFrequency_);
}

} // namespace gr::jammingSource

