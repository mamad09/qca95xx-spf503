/*

 * Copyright (c) 2002-2010, Atheros Communications Inc.

 *

 * Permission to use, copy, modify, and/or distribute this software for any

 * purpose with or without fee is hereby granted, provided that the above

 * copyright notice and this permission notice appear in all copies.

 *

 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES

 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF

 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR

 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES

 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN

 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF

 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

 */
/*
 * Copyright (c) 2013 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */

#include "dfs.h"
#include <ieee80211_var.h>
#ifdef ATH_SUPPORT_DFS

void
dfs_print_delayline(struct ath_dfs *dfs, struct dfs_delayline *dl)
{
	int i=0,index;
	struct dfs_delayelem *de;
	index = dl->dl_firstelem;

 	for (i=0; i<dl->dl_numelems; i++) {
		de = &dl->dl_elems[index];
		DFS_DPRINTK(dfs, ATH_DEBUG_DFS2,
			"Elem %u: ts=%llu diff_ts=%u (0x%x) dur=%u, seg_id=%d sidx=%d delta_peak=%d seq_num=%d\n",i, de->de_ts,
		       de->de_time, de->de_time, de->de_dur, de->de_seg_id, de->de_sidx, de->de_delta_peak, de->de_seq_num);
		index = (index + 1)& DFS_MAX_DL_MASK;
	}
}
void
dfs_print_filter(struct ath_dfs *dfs, struct dfs_filter *rf)
{

	DFS_DPRINTK(dfs, ATH_DEBUG_DFS1,
	    "filterID[%d] rf_numpulses=%u; rf->rf_minpri=%u; "
	    "rf->rf_maxpri=%u; rf->rf_threshold=%u; rf->rf_filterlen=%u; "
	    "rf->rf_mindur=%u; rf->rf_maxdur=%u\n",
	    rf->rf_pulseid,
	    rf->rf_numpulses,
	    rf->rf_minpri,
	    rf->rf_maxpri,
	    rf->rf_threshold,
	    rf->rf_filterlen,
	    rf->rf_mindur,
	    rf->rf_maxdur);
}

void
dfs_print_filters(struct ath_dfs *dfs)
{
        struct dfs_filtertype *ft = NULL;
        struct dfs_filter *rf;
        int i,j;

        if (dfs == NULL) {
                DFS_DPRINTK(dfs, ATH_DEBUG_DFS, "%s: sc_dfs is NULL\n", __func__);
                return;
        }
        for (i=0; i<DFS_MAX_RADAR_TYPES; i++) {
		if (dfs->dfs_radarf[i] != NULL) {
                    ft = dfs->dfs_radarf[i];
                    if((ft->ft_numfilters > DFS_MAX_NUM_RADAR_FILTERS) || (!ft->ft_numfilters)) 
                        continue;
                    DFS_PRINTK("===========ft->ft_numfilters=%u===========\n", ft->ft_numfilters);
                    for (j=0; j<ft->ft_numfilters; j++) {
                        rf = &(ft->ft_filters[j]);
                        DFS_PRINTK("filter[%d] filterID = %d rf_numpulses=%u; rf->rf_minpri=%u; rf->rf_maxpri=%u; rf->rf_threshold=%u; rf->rf_filterlen=%u; rf->rf_mindur=%u; rf->rf_maxdur=%u\n",j, rf->rf_pulseid,
                        rf->rf_numpulses, rf->rf_minpri, rf->rf_maxpri, rf->rf_threshold, rf->rf_filterlen, rf->rf_mindur, rf->rf_maxdur);
                    }
            }
    }
}

void dfs_print_activity(struct ath_dfs *dfs)
{
    int chan_busy=0, ext_chan_busy=0;
    u_int32_t rxclear=0, rxframe=0, txframe=0, cycles=0;

    cycles = dfs->ic->ic_get_mib_cycle_counts_pct(dfs->ic, &rxclear, &rxframe, &txframe);
    chan_busy = cycles;

    ext_chan_busy = dfs->ic->ic_get_ext_busy(dfs->ic);

    DFS_DPRINTK(dfs, ATH_DEBUG_DFS,"cycles=%d rxclear=%d rxframe=%d"
                " txframe=%d extchanbusy=%d\n", cycles, rxclear, 
                rxframe, txframe, ext_chan_busy);
    return;
}

/*
 * XXX migrate this to use ath_dfs as the arg, not ieee80211com!
 */
#ifndef ATH_DFS_RADAR_DETECTION_ONLY
OS_TIMER_FUNC(dfs_debug_timeout)
{
    struct ieee80211com *ic;
    struct ath_dfs* dfs;

    OS_GET_TIMER_ARG(ic, struct ieee80211com *);

    dfs = (struct ath_dfs *)ic->ic_dfs;

    dfs_print_activity(dfs);

    OS_SET_TIMER(&dfs->ath_dfs_debug_timer, DFS_DEBUG_TIMEOUT_MS);
}
#endif

#endif /* ATH_SUPPORT_DFS */
