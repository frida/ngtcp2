project('ngtcp2', 'c', version: '1.0.90')

lt_cur = 16
lt_rev = 0
lt_age = 0

version = meson.project_version()
version_num = run_command(
  import('python').find_installation('python3'), '-c', f'''
major, minor, patch = [int(digit) for digit in '@version@'.split('.')]
print("0x{:02x}{:02x}{:02x}".format(major, minor, patch))''',
  check: true,
).stdout().strip()

if host_machine.system() in ['hpux', 'netbsd', 'openbsd', 'sunos']
  library_version = '@0@.@1@'.format(lt_cur, lt_rev)
elif host_machine.system() == 'qnx'
  library_version = lt_cur.to_string()
else
  library_version = '@0@.@1@.@2@'.format(lt_cur - lt_age, lt_age, lt_rev)
endif

cc = meson.get_compiler('c')

cdata = configuration_data()

have_openssl = false
openssl_dep = dependency('openssl', required: false)
if openssl_dep.found()
  if cc.has_header_symbol('openssl/ssl.h', 'SSL_is_quic', dependencies: [openssl_dep])
    have_openssl = true
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

system_symbols = [
  ['be64toh', 'endian.h'],
  ['be64toh', 'sys/endian.h'],
  ['bswap_64', 'byteswap.h'],
]
foreach s : system_symbols
  if cc.has_header_symbol(s[1], s[0])
    cdata.set('HAVE_' + s[0].to_upper(), 1)
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
