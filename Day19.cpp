#include <iostream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>

int category2index( char ch )
{
  if( ch == 'x' ){ return 0; }
  if( ch == 'm' ){ return 1; }
  if( ch == 'a' ){ return 2; }
  if( ch == 's' ){ return 3; }
  std::cout << "What??\n";
  return -1;
}

struct part_t
{
  int category[4];
};

struct workflow_t
{
  struct element_t
  {
    constexpr static int COMPARE_NO = 0;
    constexpr static int COMPARE_LESS = 1;
    constexpr static int COMPARE_GREATER = 2;

    int category_index;
    int compare_op;
    int compare_value;
    std::string to;

    std::string operator()( part_t const& p ) const
    {
      if( compare_op == COMPARE_NO ){ return to; }
      if( compare_op == COMPARE_LESS )
      {
        return p.category[category_index] < compare_value ? to : "";
      }else if( compare_op == COMPARE_GREATER )
      {
        return p.category[category_index] > compare_value ? to : "";
      }
      std::cout << "What????\n";
      return "";
    }
  };

  std::string name;
  std::vector<element_t> flows;

  std::string operator()( part_t const& p ) const
  {
    for( auto &i : flows )
    {
      auto next = i(p);
      if( next.empty() == false ){ return next; }
    }
    std::cout << "What???????\n";
    return "";
  }
};

int main()
{
  /*
  std::string str =
"px{a<2006:qkq,m>2090:A,rfg}\n"
"pv{a>1716:R,A}\n"
"lnx{m>1548:A,A}\n"
"rfg{s<537:gd,x>2440:R,A}\n"
"qs{s>3448:A,lnx}\n"
"qkq{x<1416:A,crn}\n"
"crn{x>2662:A,R}\n"
"in{s<1351:px,qqz}\n"
"qqz{s>2770:qs,m<1801:hdj,R}\n"
"gd{a>3333:R,R}\n"
"hdj{m>838:A,pv}\n"
"\n"
"{x=787,m=2655,a=1222,s=2876}\n"
"{x=1679,m=44,a=2067,s=496}\n"
"{x=2036,m=264,a=79,s=2244}\n"
"{x=2461,m=1339,a=466,s=291}\n"
"{x=2127,m=1623,a=2188,s=1013}";
  std::istringstream input_file( str );
  */
  std::ifstream input_file( "../inputs/Day19.txt" );

  std::string line;

  // parse workflows
  std::map< std::string, workflow_t > workflows;
  while( 1 )
  {
    std::getline( input_file, line );
    if( line.empty() ){ break; }

    auto left_curly = line.find( '{' );
    auto right_curly = line.find( '}' );

    std::string name = line.substr( 0, left_curly );
    workflow_t workflow;
    workflow.name = name;

    std::string body = line.substr( left_curly+1, (right_curly-(left_curly+1)) );
    std::istringstream body_stream( std::move(body) );
    std::string flow_string;

    while( std::getline(body_stream,flow_string,',') )
    {
      workflow_t::element_t flow;
      auto colon_pos = flow_string.find( ':' );

      // no compare operation
      if( colon_pos == flow_string.npos )
      {
        flow.compare_op = flow.COMPARE_NO;
        flow.to = flow_string;
      }else
      {
        char category_name = flow_string[0];
        char comparer = flow_string[1];
        int compare_value = std::stoi( flow_string.substr(2,colon_pos-2) );
        std::string to_name = flow_string.substr( colon_pos+1, flow_string.size()-(colon_pos+1) );
        flow.compare_op = comparer == '<' ? flow.COMPARE_LESS : flow.COMPARE_GREATER;
        flow.compare_value = compare_value;
        flow.category_index = category2index(category_name);
        flow.to = to_name;
      }
      std::cout << flow.category_index << ", " << flow.compare_op << ", " << flow.compare_value << ", " << flow.to << "\n";
      workflow.flows.push_back( flow );
    }

    workflows[ workflow.name ] = workflow;
  }
  workflows["A"].name = "A";
  workflows["R"].name = "R";


  int answer = 0;
  // parse parts
  while( std::getline( input_file, line ) )
  {
    part_t part;
    line = line.substr( 1, line.size()-2 );
    std::istringstream line_stream( line );
    std::string category_string;
    while( std::getline(line_stream,category_string,',') )
    {
      char category_name = category_string[0];
      int value = std::stoi( category_string.substr(2,category_string.size()-2) );

      part.category[ category2index(category_name) ] = value;
    }

    std::cout << part.category[0] << ", ";
    std::cout << part.category[1] << ", ";
    std::cout << part.category[2] << ", ";
    std::cout << part.category[3] << "\n";

    workflow_t workflow = workflows["in"];
    while( 1 )
    {
      std::cout << workflow.name << "\n";
      workflow = workflows[workflow( part )];
      if( workflow.name.empty() ){ break; }
      if( workflow.name == "A" )
      {
        std::cout << "Accepted\n";
        answer += part.category[0];
        answer += part.category[1];
        answer += part.category[2];
        answer += part.category[3];
        break;
      }else if( workflow.name == "R" )
      {
        std::cout << "Rejected\n";
        break;
      }
    }
  }

  std::cout << answer << "\n";
  
  return 0;
}
