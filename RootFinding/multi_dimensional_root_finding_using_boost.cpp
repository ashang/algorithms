/*
 * =====================================================================================
 *
 *       Filename:  multi_dimensional_root_finding_using_boost.cpp
 *
 *    Description:  Compute root of a multi-dimensional system using boost
 *    libraries.
 *
 *        Version:  1.0
 *        Created:  04/13/2016 11:31:37 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Dilawar Singh (), dilawars@ncbs.res.in
 *   Organization:  NCBS Bangalore
 *
 * =====================================================================================
 */

#include <iostream>
#include <sstream>
#include <array>
#include <functional>


using namespace std;

typedef double value_type;

// A sysmte of non-linear equations. Store the values in result.
template< size_t SystemSize>
class NonlinearSystem
{
public:

    typedef std::array<value_type, SystemSize> vector_type;
    typedef std::array<vector_type, SystemSize> matrix_type;

    typedef function<value_type( void )> equation_type;

    NonlinearSystem( ) {}

    NonlinearSystem( const vector_type& x) : state( x )
    {
        auto eq0 = [this]( ) { 
            return 1.0 * (1.0 - state[0]);
        };
        auto eq1 = [this]() {
            return 10 * ( state[1] - state[0] * state[0]);
        };
        system[0] = eq0;
        system[1] = eq1;
    }


    vector_type apply(const vector_type& x)
    {
        iter += 1;
        state[0] = system[0]();
        state[1] = system[1]();
        return state;
    }

    void compute_jacobian( )
    {
        double step = 0.001;
    
    }

    string to_string( )
    {
        stringstream ss;

        ss << "Iter: " << iter << " State: ";
        for ( auto v : state ) ss << v << ",";

        return ss.str();
    }

    /**
     * @brief Stores the equations of system in an array. Each equation is a
     * lambda expression.
     */
    std::array< equation_type, SystemSize > system;
    vector_type state;
    matrix_type jacobian;
    size_t iter = 0;
    const size_t size = SystemSize;
};

template< size_t N >
void find_roots( NonlinearSystem<N>& sys 
        , const value_type& a
        , const value_type& b
        , unsigned int eps_tolerance = 30
        , size_t max_iter = 100
        )
{
    cout << sys.to_string( ) << endl;
    sys.apply( sys.state );
    cout << sys.to_string( ) << endl;

}

int main( )
{
    cerr << "This program computes the root of system described here "
        << "https://Filenamew.gnu.org/software/gsl/manual/html_node/Example-programs-for-Multidimensional-Root-finding.html#Example-programs-for-Multidimensional-Root-finding"
        << endl;

    const size_t systemSize = 2;
    array<value_type, systemSize> init { {2.0, 3.0 } }; 

    NonlinearSystem<systemSize> sys(init);
    find_roots<systemSize>(sys, 1.0, 2.0);

    return 0;
}