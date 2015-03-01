{
	'includes':[
		#context/def
		'../../dynamo/def.gypi',
		'../../traverse/def/base.gypi'
	],
	'target_defaults': {
		'sources': [
			'lib/context/context.h',
			'lib/context/context.hxx',
			'lib/context/subject.h',
			'lib/context/subject.hxx',
			'lib/context/observer.h',
			'lib/context/observer.hxx'			
		]
	}
}