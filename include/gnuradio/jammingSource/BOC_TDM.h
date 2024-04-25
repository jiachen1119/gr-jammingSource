/* -*- c++ -*- */
/*
 * Copyright 2024 SEU tang.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_JAMMINGSOURCE_BOC_TDM_H
#define INCLUDED_JAMMINGSOURCE_BOC_TDM_H

#include <gnuradio/jammingSource/api.h>
#include <gnuradio/sync_block.h>

namespace gr::jammingSource {

/*!
 * \brief <+description of block+>
 * \ingroup jammingSource
 *
 */
class JAMMINGSOURCE_API BOC_TDM : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<BOC_TDM> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of jammingSource::BOC_TDM.
     *
     * To avoid accidental use of raw pointers, jammingSource::BOC_TDM's
     * constructor is in a private implementation
     * class. jammingSource::BOC_TDM::make is the public interface for
     * creating new instances.
     */
    static sptr make(float sample_freq = 30e6, float period = 0.01, float proportion = 10.7157);

    virtual float sampling_freq() const = 0;
    virtual void set_sampling_freq(float sampling_freq) = 0;

    virtual float period() const = 0;
    virtual void set_period(float period) = 0;

    virtual float proportion() const = 0;
    virtual void set_proportion(float period) = 0;
};

} // namespace gr::jammingSource

#endif /* INCLUDED_JAMMINGSOURCE_BOC_TDM_H */
