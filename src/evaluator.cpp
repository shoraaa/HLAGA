#ifndef __EVALUATOR__
#include "evaluator.h"
#endif

#include "kd_tree.h"
#include <vector>
#include <utility>
#include <tuple>
#include <iostream>

TEvaluator::TEvaluator()
{
  fEdgeDis = NULL;
  fNearCity = NULL;
  Ncity = 0;
  fNearNumMax = 50;  
}

TEvaluator::~TEvaluator()
{
  // printf( "Destructor of TEvaluator\n" );
  for ( int i = 0; i < Ncity; ++i ) 
    delete[] fEdgeDis[ i ];
  delete[] fEdgeDis;
  for ( int i = 0; i < Ncity; ++i ) 
    delete[] fNearCity[ i ];
  delete[] fNearCity;
  
  delete [] x;
  delete [] y;
  // printf( "Finish Destructor of TEvaluator\n" );
}

void TEvaluator::SetInstance(int Ncity) {
  this->Ncity = Ncity;
  fEdgeDis = new int64_t* [ Ncity ];
  for( int i = 0; i < Ncity; ++i ) fEdgeDis[ i ] = new int64_t [ Ncity ];
  fNearCity = new int* [ Ncity ];
  for( int i = 0; i < Ncity; ++i ) fNearCity[ i ] = new int [ fNearNumMax+1 ];

  x = new double [ Ncity ]; 
  y = new double [ Ncity ]; 

}

void TEvaluator::SetInstance(const std::vector<uint32_t> &checklist, const std::vector<Vec2d> &coords, const std::vector<std::pair<uint32_t, uint32_t>> &fixed_edges, const std::function<double (uint32_t, uint32_t)>& cost_fn) {
  Ncity = checklist.size();

  for (int i = 0; i < Ncity; ++i) {
    x[i] = coords[i].x_;
    y[i] = coords[i].y_;
  }

  int checkedN[ Ncity ];

  for( int i = 0; i < Ncity ; ++i )
  {
    for( int j = 0; j < Ncity ; ++j )
    {
      fEdgeDis[ i ][ j ] = static_cast<int64_t>(cost_fn(checklist[i], checklist[j]));
      // fEdgeDis[ i ][ j ]= static_cast<int32_t>((coords[i] - coords[j]).length() + 0.5);
      // fEdgeDis[ i ][ j ]=static_cast<int32_t>(std::ceil((coords[i] - coords[j]).length()));
    }
  }

  for (auto& [a, b] : fixed_edges) {
    fEdgeDis[a][b] = -1e9;
    fEdgeDis[b][a] = -1e9;
  } 

  int ci;
  int j1 ,j2 ,j3;
  int city_num = 0;
  int64_t min_dis;

  for( ci = 0; ci < Ncity; ++ci )
  {
    for( j3 = 0; j3 < Ncity; ++j3 ) checkedN[ j3 ] = 0;
    checkedN[ ci ] = 1;
    fNearCity[ ci ][ 0 ] = ci;
    for( j1 = 1; j1 <= fNearNumMax; ++j1 ) 
    {
      min_dis = 1e9;
      for( j2 = 0; j2 < Ncity; ++j2 )
      { 
        if( fEdgeDis[ ci ][ j2 ] <= min_dis && checkedN[ j2 ] == 0 )
        {
          city_num = j2;
                min_dis = fEdgeDis[ ci ][ j2 ];
        }
            }
            fNearCity[ ci ][ j1 ] = city_num;
            checkedN[ city_num ] = 1;
          }
        }
}

void TEvaluator::DoIt( TIndi& indi )
{
  int64_t d;
  d = 0;  
  for( int i = 0; i < Ncity; ++i )
  {  
    d = d + fEdgeDis[ i ][ indi.fLink[i][0] ];
    d = d + fEdgeDis[ i ][ indi.fLink[i][1] ];
  }
  indi.fEvaluationValue = d/2;
}


void TEvaluator::WriteTo( FILE* fp, TIndi& indi ) 
{
  assert( Ncity == indi.fN );
  int Array[ Ncity ];
  int curr, next, pre, st, count;

  count = 0;
  pre = -1;
  curr = 0;
  st = 0;
  while( 1 )
  {
    Array[ count++ ] = curr + 1;

    if( count > Ncity ){
      printf( "Invalid\n" );
      return;
    } 
 
    if( indi.fLink[ curr ][ 0 ] == pre )
      next = indi.fLink[ curr ][ 1 ];
    else 
      next = indi.fLink[ curr ][ 0 ];

    pre = curr;
    curr = next;
    if( curr == st )
      break;
  }

  if( this->CheckValid( Array, indi.fEvaluationValue ) == false ){
    printf( "Individual is invalid \n" );
  }

  fprintf( fp, "%d %d\n", indi.fN, indi.fEvaluationValue );
  for( int i = 0; i < indi.fN; ++i )
    fprintf( fp, "%d ", Array[ i ] );
  fprintf( fp, "\n" ); 
}


bool TEvaluator::ReadFrom( FILE* fp, TIndi& indi )
{
  assert( Ncity == indi.fN );
  int Array[ Ncity ];
  int curr, next, pre, st, count;
  int N, value;

  if( fscanf( fp, "%d %d", &N, &value ) == EOF ) 
    return false;
  assert( N == Ncity );
  indi.fN = N;
  indi.fEvaluationValue = value;

  for( int i = 0; i < Ncity; ++i ){ 
    if( fscanf( fp, "%d", &Array[ i ] ) == EOF )
      return false;
  }

  if( this->CheckValid( Array, indi.fEvaluationValue ) == false ){
    printf( "Individual is invalid \n" );
    return false;
  }

  for( int i = 0; i < Ncity; ++i ){ 
    Array[ i ] -= 1; 
  }

  for( int i = 1; i < Ncity-1; ++i ){ 
    indi.fLink[ Array[ i ] ][ 0 ] = Array[ i-1 ]; 
    indi.fLink[ Array[ i ] ][ 1 ] = Array[ i+1 ]; 
  }
  indi.fLink[ Array[ 0 ] ][ 0 ] = Array[ Ncity-1 ]; 
  indi.fLink[ Array[ 0 ] ][ 1 ] = Array[ 1 ]; 
  indi.fLink[ Array[ Ncity-1 ] ][ 0 ] = Array[ Ncity-2 ]; 
  indi.fLink[ Array[ Ncity-1 ] ][ 1 ] = Array[ 0 ]; 

  return true;
}    


bool TEvaluator::CheckValid( int* array, int value )
{
  int check[ Ncity ];
  int64_t distance;

  for( int i = 0; i < Ncity; ++i ){
    check[ i ] = 0;
  }

  for( int i = 0; i < Ncity; ++i )
    ++check[ array[ i ]-1 ];

  for( int i = 0; i < Ncity; ++i ){
    if( check[ i ] != 1 ){
      return false;
    }
  }
    
  distance = 0;  
  for( int i = 0; i < Ncity-1; ++i ){
    distance += fEdgeDis[ array[ i ]-1 ][ array[ i+1 ]-1 ];
  }
  distance += fEdgeDis[ array[ Ncity-1 ]-1 ][ array[ 0 ]-1 ];
  if( distance != value ){
    return false;
  }
  return true;
}
