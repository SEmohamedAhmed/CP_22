
void ordered_set__(){
    #include <ext/pb_ds/assoc_container.hpp>
    #include <ext/pb_ds/tree_policy.hpp>
    using namespace __gnu_pbds;
    #define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
    ordered_set s;
    s.insert(1);
    s.insert(5);
    // Finding the (k+1)th min element in the set
    cout << *s.find_by_order(0)<<el;
    // Finding the number of elements || position in a sorted 0-based array
    // strictly less than k = 5
    cout << s.order_of_key(5);
}
/**********************************************************************************************************************************************************************/
