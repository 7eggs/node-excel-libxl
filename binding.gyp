{
  'targets': [
    {
      'target_name': 'liblibxl_bindings',
      'sources': [
        'src/libxl_bindings.cc',
        'src/libxl_book.cc',
        'src/libxl_sheet.cc',
        'src/libxl_format.cc',
        'src/libxl_font.cc',
        'src/string_utils.cc'
      ],
      'conditions': [
        ['OS=="linux"', {
          'conditions': [
            ['target_arch=="ia32"', {
              'link_settings': {
                'ldflags': ['-L../deps/libxl/lib']
              }
            }],
            ['target_arch=="x64"', {
              'link_settings': {
                'ldflags': ['-L../deps/libxl/lib64']
              }
            }]
          ],
          'include_dirs': [
            'deps/libxl/include_cpp'
          ],
          'libraries': [
            '-lxl'
          ]
        }, {
          # only Linux is supported now ...
        }]
      ]
    }
  ]
}