sources = shared_crypto_sources + 'ossl.c'

libngtcp2_crypto_ossl = library('ngtcp2_crypto_ossl', sources,
  version: crypto_ossl_library_version,
  include_directories: [internal_incdirs, public_incdirs],
  dependencies: [openssl_dep, libngtcp2_dep],
  install: true,
)

libngtcp2_crypto_ossl_dep = declare_dependency(
  include_directories: public_incdirs,
  link_with: libngtcp2_crypto_ossl,
  dependencies: [libngtcp2_dep],
)

pkg = import('pkgconfig')
pkg.generate(libngtcp2_crypto_ossl,
  filebase: 'libngtcp2_crypto_ossl',
  description: 'ngtcp2 ossl crypto library',
  url: 'https://github.com/ngtcp2/ngtcp2',
)

meson.override_dependency('libngtcp2_crypto_ossl', libngtcp2_crypto_ossl_dep)
