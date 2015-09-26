{
	'includes':[
		'lib/context/def.gypi',
	],#includes
	'target_defaults': {
		'target_name': 'test', 
		'type': 'executable',
		'sources': [
			'src/base.h',
			'src/base.hxx',
			'src/context_test.h',
			'src/main.cpp',
			'src/math_test.h',
		], #sources
		'include_dirs': [
			'.'
		], #include_dirs		
	}, #target_defaults
}