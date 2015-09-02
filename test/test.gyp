{
	'includes':[
		'lib/context/def.gypi',
		'plank/def/plank.gypi',
	],#includes
	'target_defaults': {
		'target_name': 'test', 
		'type': 'executable',
		'sources': [
			'src/base.h',
			'src/base.hxx',
			'src/context_test.h',
			'src/main.cpp',
		], #sources
		'include_dirs': [
			'plank/src/',
			'.'
		], #include_dirs		
	}, #target_defaults
}