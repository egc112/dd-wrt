// SPDX-License-Identifier: BSD-3-Clause
/*
 * BSD 3-Clause Clear License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Copyright (c) 2016-2020, Yann Collet, Facebook, Inc.
 * Copyright (c) 2019-2020, Michael Niewöhner
 * Copyright (c) 2020, Kjeld Schouten-Lebbing
 */

#define	MEM_MODULE
#define	XXH_NAMESPACE ZSTD_
#define	XXH_PRIVATE_API
#define	XXH_INLINE_ALL
#define	ZSTD_LEGACY_SUPPORT 0
#define	ZSTD_LIB_DICTBUILDER 0
#define	ZSTD_LIB_DEPRECATED 0
#define	ZSTD_NOBENCH
#define	ZSTD_NODICT
#define	ZSTD_NO_INTRINSICS
#define	ZSTD_NO_UNUSED_FUNCTIONS
#define	ZSTD_ADDRESS_SANITIZER 0
#define	ZSTD_MEMORY_SANITIZER 0

/* Include zstd_deps.h first with all the options we need enabled. */
#define	ZSTD_DEPS_NEED_MALLOC
#define	ZSTD_DEPS_NEED_MATH64
#include "common/zstd_deps.h"

#include "common/debug.c"
#include "common/entropy_common.c"
#include "common/error_private.c"
#include "common/fse_decompress.c"
#include "common/pool.c"
#include "common/zstd_common.c"
#include "common/zstd_trace.c"

#include "compress/fse_compress.c"
#include "compress/hist.c"
#include "compress/huf_compress.c"
#include "compress/zstd_compress_literals.c"
#include "compress/zstd_compress_sequences.c"
#include "compress/zstd_compress_superblock.c"
#include "compress/zstd_compress.c"
#include "compress/zstd_double_fast.c"
#include "compress/zstd_fast.c"
#include "compress/zstd_lazy.c"
#include "compress/zstd_ldm.c"
#include "compress/zstd_opt.c"

#include "decompress/huf_decompress.c"
#include "decompress/zstd_ddict.c"
#include "decompress/zstd_decompress.c"
#include "decompress/zstd_decompress_block.c"
