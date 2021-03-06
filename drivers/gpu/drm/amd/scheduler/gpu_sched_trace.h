/*
 * Copyright 2017 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#if !defined(_GPU_SCHED_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#define _GPU_SCHED_TRACE_H_

#include <drm/drmP.h>

static inline void
trace_amd_sched_job(void* sched_job){
	CTR1(KTR_DRM, "amd_sched_job %p",sched_job);
}

static inline void
trace_amd_sched_process_job(void* s_fence){
	CTR1(KTR_DRM, "amd_process_sched_job %p",s_fence);
}

#ifdef __linux__
#undef TRACE_SYSTEM
#define TRACE_SYSTEM gpu_sched
#define TRACE_INCLUDE_FILE gpu_sched_trace

TRACE_EVENT(amd_sched_job,
	    TP_PROTO(struct amd_sched_job *sched_job),
	    TP_ARGS(sched_job),
	    TP_STRUCT__entry(
			     __field(struct amd_sched_entity *, entity)
			     __field(struct dma_fence *, fence)
			     __field(const char *, name)
			     __field(uint64_t, id)
			     __field(u32, job_count)
			     __field(int, hw_job_count)
			     ),

	    TP_fast_assign(
			   __entry->entity = sched_job->s_entity;
			   __entry->id = sched_job->id;
			   __entry->fence = &sched_job->s_fence->finished;
			   __entry->name = sched_job->sched->name;
			   __entry->job_count = kfifo_len(
				   &sched_job->s_entity->job_queue) / sizeof(sched_job);
			   __entry->hw_job_count = atomic_read(
				   &sched_job->sched->hw_rq_count);
			   ),
	    TP_printk("entity=%p, id=%llu, fence=%p, ring=%s, job count:%u, hw job count:%d",
		      __entry->entity, __entry->id,
		      __entry->fence, __entry->name,
		      __entry->job_count, __entry->hw_job_count)
);

TRACE_EVENT(amd_sched_process_job,
	    TP_PROTO(struct amd_sched_fence *fence),
	    TP_ARGS(fence),
	    TP_STRUCT__entry(
		    __field(struct dma_fence *, fence)
		    ),

	    TP_fast_assign(
		    __entry->fence = &fence->finished;
		    ),
	    TP_printk("fence=%p signaled", __entry->fence)
);
#endif /* __linux__ */

#endif
