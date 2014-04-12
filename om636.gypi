{
	'target_defaults': {
		'cflags': [ '-std=c++11', '-stdlib=libc++' ],
		'ldflags': [ '-stdlib=libc++' ],
		'sources': [ 
			'src/core/assert.cpp', 
			'src/core/assert.h',
			'src/core/assert.hxx',
			'src/core/chain.h',
			'src/core/chain.hxx',
			'src/core/constraints.h',
			'src/core/constraints.hxx',
			'src/core/core.h',
			'src/core/core.hxx',
			'src/core/corefwd.h',
			'src/core/persistent.h',
			'src/core/persistent.hxx',
			'src/core/tests.h',
			'src/core/tests.hxx',
			'src/core/traverse.h',
			'src/core/traverse.hxx',
			'src/core/typetraits.h',
			'src/core/typeutills.h',
		] #sources
	}
}