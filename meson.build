project('ngtcp2', 'c', version: '1.26.0', default_options: ['c_std=gnu11,c11'])

lt_cur = 27
lt_rev = 0
lt_age = 11

crypto_quictls_lt_cur = 7
crypto_quictls_lt_rev = 2
crypto_quictls_lt_age = 5

crypto_ossl_lt_cur = 3
crypto_ossl_lt_rev = 1
crypto_ossl_lt_age = 3

version = meson.project_version()
version_num = run_command(
  import('python').find_installation('python3'), '-c', f'''
major, minor, patch = [int(digit) for digit in '@version@'.split('.')]
print("0x{:02x}{:02x}{:02x}".format(major, minor, patch))''',
  check: true,
).stdout().strip()

if host_machine.system() in ['hpux', 'netbsd', 'openbsd', 'sunos']
  library_version = '@0@.@1@'.format(lt_cur, lt_rev)
  crypto_quictls_library_version = '@0@.@1@'.format(crypto_quictls_lt_cur, crypto_quictls_lt_rev)
  crypto_ossl_library_version = '@0@.@1@'.format(crypto_ossl_lt_cur, crypto_ossl_lt_rev)
elif host_machine.system() == 'qnx'
  library_version = lt_cur.to_string()
  crypto_quictls_library_version = crypto_quictls_lt_cur.to_string()
  crypto_ossl_library_version = crypto_ossl_lt_cur.to_string()
else
  library_version = '@0@.@1@.@2@'.format(lt_cur - lt_age, lt_age, lt_rev)
  crypto_quictls_library_version = '@0@.@1@.@2@'.format(crypto_quictls_lt_cur - crypto_quictls_lt_age, crypto_quictls_lt_age, crypto_quictls_lt_rev)
  crypto_ossl_library_version = '@0@.@1@.@2@'.format(crypto_ossl_lt_cur - crypto_ossl_lt_age, crypto_ossl_lt_age, crypto_ossl_lt_rev)
endif

cc = meson.get_compiler('c')

if meson.is_subproject() and cc.get_argument_syntax() != 'msvc'
  add_project_arguments('-w', language: 'c')
endif

cdata = configuration_data()

have_quictls = false
have_ossl = false
openssl_dep = dependency('openssl', required: false)
if openssl_dep.found()
  if openssl_dep.type_name() == 'internal'
    have_ossl = openssl_dep.version().version_compare('>=3.5')
    have_quictls = not have_ossl
  elif cc.has_header_symbol('openssl/ssl.h', 'SSL_set_quic_tls_cbs', dependencies: [openssl_dep])
    have_ossl = true
  elif cc.has_header_symbol('openssl/ssl.h', 'SSL_is_quic', dependencies: [openssl_dep]) and cc.has_type('SSL_QUIC_METHOD', prefix: '#include <openssl/ssl.h>', dependencies: [openssl_dep])
    have_quictls = true
  else
    warning('Disabling crypto support due to lack of QUIC support in OpenSSL')
  endif
endif

system_headers = [
  'byteswap.h',
  'endian.h',
  'arpa/inet.h',
  'netinet/in.h',
  'sys/endian.h',
  'unistd.h',
]
foreach h : system_headers
  if cc.check_header(h)
    cdata.set('HAVE_' + h.underscorify().to_upper(), 1)
  endif
endforeach

cdata.set10('HAVE_DECL_BE64TOH', cc.has_header_symbol('endian.h', 'be64toh') or cc.has_header_symbol('sys/endian.h', 'be64toh'))
cdata.set10('HAVE_DECL_BSWAP_64', cc.has_header_symbol('byteswap.h', 'bswap_64'))

foreach f : ['explicit_bzero', 'memset_s']
  if cc.has_function(f)
    cdata.set('HAVE_' + f.to_upper(), 1)
  endif
endforeach

if host_machine.endian() == 'big'
  cdata.set('WORDS_BIGENDIAN', 1)
endif

configure_file(
  configuration: cdata,
  output: 'config.h'
)

add_project_arguments(
  '-DBUILDING_NGTCP2',
  '-DHAVE_CONFIG_H',
  language: 'c'
)

public_cflags = []
if get_option('default_library') == 'static'
  public_cflags += '-DNGTCP2_STATICLIB'
endif
add_project_arguments(public_cflags, language: 'c')

public_incdirs = include_directories(
  'lib' / 'includes',
  'crypto' / 'includes',
)

internal_incdirs = include_directories(
  '.',
  'lib',
  'crypto',
)

subdir('lib')
subdir('crypto')
