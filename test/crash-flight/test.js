#!/usr/bin/env node

var fs = require( 'fs' )
  , join = require( 'path' ).join
  , Processor = require( 'mucbuc-jsthree' ).Processor
  , runDir = __dirname + (process.argv[2] ? process.argv[2] : '/../sample')
  , MAKE_PATH = './../../crash-flight/config/makefile'
  , EventEmitter = require( 'events' ).EventEmitter;
  
function execute( cmd, args, cwd, done ) {
  var e = new EventEmitter()
    , p = new Processor( { cmd: cmd, args: args, cwd: cwd }, e );
  console.log( ':node test$ ' + cmd + ' ' + args.toString() + ' ' + cwd );
  e.on( 'child_error', function() { 
    console.log( 'error' );
  } );
  e.on( 'read', function( data ) {
    console.log( data.toString() );
  } );
  e.once( 'exit', done );
  e.emit( 'execute' );
}

(function() {

  process.on( 'SIGINT', function() {
    console.log( 'error: SIGINT' );
    process.exit(1);
  } );
  
  fs.readdir( runDir, function( err, list ) {
    if (err) throw err;
    
    nextFile();

    function nextFile() {
      if (list.length)  {
        compileAndRun( list[0] );
        list = list.slice( 1, list.length );
      }
  
      function compileAndRun( file ) {

        var path = join( runDir, file ); 

        fs.stat( path, function( err, stat ) {
          if (stat && stat.isDirectory()) {
          
            console.log( 'testing ' + path + ':' );
    
            execute( 'make', [ '-f', MAKE_PATH, 'run' ], path, function() {
              execute( 'make', [ '-f', MAKE_PATH, 'clean' ], path, nextFile );
            } );
          } 
          else {
            nextFile();
          }
        } );
      }
    }

  } );
})();
