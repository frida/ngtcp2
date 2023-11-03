sources = shared_crypto_sources + 'quictls.c'

libngtcp2_crypto_quictls = library('ngtcp2_crypto_quictls', sources,
  version: library_version,
  include_directories: [internal_incdirs, public_incdirs],
  dependencies: [openssl_dep],
  install: true,
)

libngtcp2_crypto_quictls_dep = declare_dependency(
  include_directories: public_incdirs,
  link_with: libngtcp2_crypto_quictls,
  dependencies: [libngtcp2_dep],
)

pkg = import('pkgconfig')
pkg.generate(libngtcp2_crypto_quictls,
  description: 'ngtcp2 quictls crypto library',
  url: 'https://github.com/ngtcp2/ngtcp2',
)

meson.override_dependency('libngtcp2_crypto_quictls', libngtcp2_crypto_quictls_dep)
