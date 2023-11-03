subdir('includes')

sources = [
  'ngtcp2_pkt.c',
  'ngtcp2_conv.c',
  'ngtcp2_str.c',
  'ngtcp2_vec.c',
  'ngtcp2_buf.c',
  'ngtcp2_conn.c',
  'ngtcp2_mem.c',
  'ngtcp2_pq.c',
  'ngtcp2_map.c',
  'ngtcp2_rob.c',
  'ngtcp2_ppe.c',
  'ngtcp2_crypto.c',
  'ngtcp2_err.c',
  'ngtcp2_range.c',
  'ngtcp2_acktr.c',
  'ngtcp2_rtb.c',
  'ngtcp2_frame_chain.c',
  'ngtcp2_strm.c',
  'ngtcp2_idtr.c',
  'ngtcp2_gaptr.c',
  'ngtcp2_ringbuf.c',
  'ngtcp2_log.c',
  'ngtcp2_qlog.c',
  'ngtcp2_cid.c',
  'ngtcp2_ksl.c',
  'ngtcp2_cc.c',
  'ngtcp2_bbr.c',
  'ngtcp2_addr.c',
  'ngtcp2_path.c',
  'ngtcp2_pv.c',
  'ngtcp2_pmtud.c',
  'ngtcp2_version.c',
  'ngtcp2_rst.c',
  'ngtcp2_window_filter.c',
  'ngtcp2_opl.c',
  'ngtcp2_balloc.c',
  'ngtcp2_objalloc.c',
  'ngtcp2_unreachable.c',
  'ngtcp2_conversion.c',
]

libngtcp2 = library('ngtcp2', sources,
  version: library_version,
  include_directories: [internal_incdirs, public_incdirs],
  install: true,
)

libngtcp2_dep = declare_dependency(
  include_directories: public_incdirs,
  compile_args: public_cflags,
  link_with: libngtcp2,
)

pkg = import('pkgconfig')
pkg.generate(libngtcp2,
  filebase: 'libngtcp2',
  description: 'ngtcp2 library',
  url: 'https://github.com/ngtcp2/ngtcp2',
  extra_cflags: public_cflags,
)

meson.override_dependency('libngtcp2', libngtcp2_dep)
