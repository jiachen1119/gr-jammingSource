/* -*- c++ -*- */
/*
 * Copyright 2024 SEU tang.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_JAMMINGSOURCE_BOC_H
#define INCLUDED_JAMMINGSOURCE_BOC_H

#include <gnuradio/jammingSource/api.h>
#include <gnuradio/sync_block.h>

namespace gr::jammingSource {

/*!
 * \brief this block is designed to produce the matched spectrum jamming, especially for the BOC gnss signal
 * \ingroup jammingSource
 *
 */
class JAMMINGSOURCE_API BOC : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<BOC> sptr;

    static sptr make(int a = 10, int b = 5, float sampling_freq = 30e6);

    virtual double sampling_freq() const = 0;

    /*!
     * Sets the sampling frequency of the signal.
     * \param sampling_freq sampling frequency
     */
    virtual void set_sampling_freq(float sampling_freq) = 0;

};

} // namespace gr::jammingSource


#endif /* INCLUDED_JAMMINGSOURCE_BOC_H */
