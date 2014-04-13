{
	'includes': [
		'lib/om636/om636.gypi',
	], 
	'target_defaults': {
		'include_dirs': [
			'.'
		], #include_dirs
		'sources': [ 
			'src/observer.h',
			'src/observer.hxx',
			'src/presenter.h',
			'src/presenter.hxx',
			'src/view.h',
			'src/view.hxx'
		], #sources
		'cflags': [ '-std=c++11', '-stdlib=libc++' ],
		'ldflags': [ '-stdlib=libc++' ],
	}
}