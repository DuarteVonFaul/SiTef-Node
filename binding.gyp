{
    "targets":[
        {
            "target_name":"node-sitef",
            "sources":[ "./lib/sitef.cpp"
                      ],
            "cflags!": [ "-fno-exceptions" ],
            "cflags_cc!": [ "-fno-exceptions" ],
            "msvs_settings": {
                "VCCLCompilerTool": { "ExceptionHandling": 1 },
            },
            "conditions": [
                [
                'OS=="win"',
                {
                    "defines": [
                    "_HAS_EXCEPTIONS=1"
                    ]
                }
                ]
            ],
            "include_dirs": ["<!@(node -p \"require('node-addon-api').include\")"],
            'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
        }
    ]
}