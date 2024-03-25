/* -*- c++ -*- */
/*
 * Copyright 2022 mortarboard-H.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_JAMMINGSOURCE_CHIRP_IMPL_H
#define INCLUDED_JAMMINGSOURCE_CHIRP_IMPL_H

#include <gnuradio/jammingSource/Chirp.h>
#include <gnuradio/fxpt_nco.h>


namespace gr::jammingSource {

enum ChirpType{
    Linear,
    Quadratic,
    Cubic,
    Exponential,
    Logarithmic,
    Trigonometric };


class Chirp_impl : public Chirp
{
private:
    ChirpType type_;
    double samplingFrequency_;
    double period_;
    double maxFrequency_;
    double minFrequency_;

    int samplesPerLoop_;
    std::vector<double> freqIncPerSample_;
    gr::fxpt_nco nco_;
    double count_;
    int freqIncCount_;

public:
    Chirp_impl(double samp_rate, double min_freq, double max_freq, double period);
    ~Chirp_impl() override;

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override;

    double sampling_freq() const override {return samplingFrequency_;}
    double period() const override {return period_;}

    void set_sampling_freq(double samp_rate) override;
    void set_period(double period) override;
    void set_max_freq(double max_freq) override;
    void set_min_freq(double min_freq) override;

    void reset_all();

};

} // namespace gr::jammingSource


#endif /* INCLUDED_JAMMINGSOURCE_CHIRP_IMPL_H */
