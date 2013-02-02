{
  'targets': [
    {
      # have to specify 'liblib' here since gyp will remove the first one :\
      'target_name': 'libxl_bindings.cc',
      'sources': [
        'src/libxl_bindings.cc',
        'src/libxl_book.cc'
      ],
      'conditions': [
        ['OS=="win"', {
          # no Windows support yet...
        }, {
          'libraries': [
            '-llept', '-ltesseract'
          ],
          'include_dirs': [
            'deps/libxl'
          ]
        }],
        ['OS=="
      ]
    }
  ]
}