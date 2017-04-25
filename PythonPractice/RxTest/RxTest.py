import rx
from rx import Observable, Observer



class MyObserver( Observer ):
    def on_next( self, value ):
        print( f"Got: {value}" )


    def on_error( self, error ):
        print( f"Got error : {error}" )


    def on_completed( self ):
        print( "Sequence completed" )



def generate_sequence_example():
    Observable.from_iterable( range( 10 ) ).subscribe( MyObserver() )
    Observable.from_iterable( range( 10 ) ).subscribe( print )



def filter_sequence_example():
    Observable.from_( range( 10 ) ).filter( lambda x: x % 2 ).subscribe( print )



def transform_sequence_example():
    Observable.from_( range( 10 ) ).map( lambda x: x * 2 ).subscribe( print )
    Observable.from_( range( 10, 20, 2 ) ).map( lambda x, i: f"{i} : {x * 2}" ).subscribe( print )



def merge_example():
    Observable.range( 1, 5 ).merge( Observable.from_("abcde") ).subscribe( print )