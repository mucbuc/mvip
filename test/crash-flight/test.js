#!/usr/bin/env node

var fs = require( 'fs' )
  , join = require( 'path' ).join
  , exec = require( 'mucbuc-jsthree' ).exec
  , runDir = __dirname + (process.argv[2] ? process.argv[2] : '/../sample')
  , MAKE_PATH = './../../crash-flight/config/makefile';
  
function execute( cmd, cwd, done ) {
  console.log( ':node test$ ' + cmd ); 
  return exec( cmd, cwd, done );
}

(function() {

  process.on( 'SIGINT', function() {
    console.log( 'error: SIGINT' );
    process.exit(1);
  } );
  
  fs.readdir( runDir, function( err, list ) {
    if (err) throw err;
    list.forEach( function( file ) {
      var path = join( runDir, file ); 

      fs.stat( path, function( err, stat ) {
        if (stat && stat.isDirectory()) {
        
          console.log( 'testing ' + path + ':' );
  
          execute( 'make -f ' + MAKE_PATH + ' run', function() {
            execute( 'make -f ' + MAKE_PATH + ' clean', function() {}, path );
          }, path );
        }
      } );
    } );
  } );
})();
