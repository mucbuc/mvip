{
	'includes':[
		'lib/sense/def.gypi',
	],#includes
	'target_defaults': {
		'target_name': 'test', 
		'type': 'executable',
		'sources': [
			'src/main.cpp',
			'src/subject.h'
		], #sources
		'include_dirs': [
			'.'
		], #include_dirs		
	}, #target_defaults
}