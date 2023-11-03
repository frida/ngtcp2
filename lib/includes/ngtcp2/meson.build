config = configuration_data()
config.set('PACKAGE_VERSION', version)
config.set('PACKAGE_VERSION_NUM', version_num)

ngtcp2ver_h = configure_file(
  input: 'version.h.in',
  output: 'version.h',
  configuration: config,
)

install_headers('ngtcp2.h', ngtcp2ver_h, subdir: 'ngtcp2')
