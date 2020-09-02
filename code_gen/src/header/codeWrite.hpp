/**
 * Library to generate code
 * Developped by Hugo LAULLIER and Thomas RIVES
 */

#ifndef CODE_WRITE
#define CODE_WRITE

#include <iostream>
#include <fstream>
#include <utility>
#include <typeinfo>
#include <string>
#include <vector>
#include <algorithm>

/**
 * Class of codeWrite
 */
class codeWrite
{
private:
    /* The output flux */
    std::ofstream fluxFile;

    /**
    * Generate recursively a function when there are no more parameters
    */
    void function_rec()
    {
        return;
    }

    /**
    * Generate recursively a function with many parameters
    * @param first: first parameter
    * @param rest : the other parameters
    */
    template <typename First, typename... Rest>
    void function_rec(First &&first, Rest &&... rest)
    {
        this->fluxFile << std::forward<First>(first);
        if (sizeof...(rest) > 0)
            this->fluxFile << ",";
        function_rec(std::forward<Rest>(rest)...);
    }

    /**
    * Generate recursively a code when there are no more parameters
    */
    void code_rec()
    {
        return;
    }

    /**
    * Generate recursively a code with many parameters
    * @param first: first parameter
    * @param rest : the other parameters
    */
    template <typename First, typename... Rest>
    void code_rec(First &&first, Rest &&... rest)
    {
        this->fluxFile << std::forward<First>(first);
        code_rec(std::forward<Rest>(rest)...);
    }
    
    /**
    * Generate recursively a "out flux" when there are no more parameters
    */
    void flux_out_rec()
    {
        return;
    }

    /**
    * Generate recursively a "out flux" with many parameters
    * @param first: first parameter
    * @param rest : the other parameters
    */
    template <typename First, typename... Rest>
    void flux_out_rec(First &&first, Rest &&... rest)
    {
        this->fluxFile << "<<" << std::forward<First>(first);
        flux_out_rec(std::forward<Rest>(rest)...);
    }

    /**
    * Generate recursively a "in flux" when there are no more parameters
    */
    void flux_in_rec()
    {
        return;
    }

    /**
    * Generate recursively a "in flux" with many parameters
    * @param first: first parameter
    * @param rest : the other parameters
    */
    template <typename First, typename... Rest>
    void flux_in_rec(First &&first, Rest &&... rest)
    {
        this->fluxFile << ">>" << std::forward<First>(first);
        flux_in_rec(std::forward<Rest>(rest)...);
    }

public:
    /**
    * Constructor of codeWrite
    * @param file: the output file
    */
    codeWrite(std::string file)
    {
        this->fluxFile.open(file);
        if (this->fluxFile.bad())
        {
            perror("System error : folder creation");
            exit(EXIT_FAILURE);
        }
    }
    
    /**
    * Destructor of codeWrite
    */
    ~codeWrite()
    {
        this->fluxFile.close();
    }

    /**
    * Flush the output flux
    */
    void flush()
    {
        this->fluxFile.flush();
    }

    /**
    * Generate a function
    * @param type: the type of the function (int, bool, char...)
    * @param name: the name of the function
    * @param args: the arguments of the function
    */
    template <typename... Args>
    void _function(std::string type, std::string name, Args &&... args)
    {
        this->fluxFile << type << " " << name << "(";
        function_rec(std::forward<Args>(args)...);
        this->fluxFile << "){";
    }

    /**
    * Generate the prototype of a function
    * @param type: the type of the function (int, bool, char...)
    * @param name: the name of the function
    * @param args: the arguments of the function
    */
    template <typename... Args>
    void _function_prot(std::string type, std::string name, Args &&... args)
    {
        this->fluxFile << type << " " << name << "(";
        function_rec(std::forward<Args>(args)...);
        this->fluxFile << ");";
    }

    /**
    * Generate just a function (without brace nor semicolon)
    * @param type: the type of the function (int, bool, char...)
    * @param name: the name of the function
    * @param args: the arguments of the function
    */
    template <typename... Args>
    void _function_free(std::string type, std::string name, Args &&... args)
    {
        this->fluxFile << type << " " << name << "(";
        function_rec(std::forward<Args>(args)...);
        this->fluxFile << ")";
    }

    /**
    * Write a opening brace
    */
    void _start()
    {
        this->fluxFile << "{";
    }
    
    /**
    * Write a closing brace
    */
    void _end()
    {
        this->fluxFile << "}";
    }

    /**
    * Write a closing brace followed by a semicolon
    */
    void _end_object()
    {
        this->fluxFile << "};";
    }

    /**
    * Write a semicolon
    */
    void _semicolon()
    {
        this->fluxFile << ";";
    }

    /**
    * Generate the end of a do while
    */
    template <typename... All>
    void do_while(All &&... all)
    {
        this->fluxFile << "}while(";
        code_rec(std::forward<All>(all)...);
        this->fluxFile << ");";
    }

    /**
    * Write a space to generate a linebreak
    */
    void _linebreak()
    {
        this->fluxFile << " ";
    }

    /**
    * Generate code
    * @param all: all the elements of the code
    */
    template <typename... All>
    void _code(All &&... all)
    {
        code_rec(std::forward<All>(all)...);
        this->fluxFile;
    }

    /**
    * Generate a "out flux"
    * @param flux: the "out flux"
    * @param rest: all the elements of the flux
    */
    template <typename... Rest>
    void _flux_out(std::string flux, Rest &&... rest)
    {
        this->fluxFile << flux;
        flux_out_rec(std::forward<Rest>(rest)...);
        this->fluxFile << ";";
    }

    /**
    * Generate a "in flux"
    * @param flux: the "in flux"
    * @param rest: all the elements of the flux
    */
    template <typename... Rest>
    void _flux_in(std::string flux, Rest &&... rest)
    {
        this->fluxFile << flux;
        flux_in_rec(std::forward<Rest>(rest)...);
        this->fluxFile << ";";
    }

    /**
    * Generate a cout
    * @param all: all the elements of the flux
    */
    template <typename... All>
    void _cout(All &&... all)
    {
        this->fluxFile << "std::cout";
        flux_out_rec(std::forward<All>(all)...);
        this->fluxFile << ";";
    }

    /**
    * Generate a cerr
    * @param all: all the elements of the flux
    */
    template <typename... All>
    void _cerr(All &&... all)
    {
        this->fluxFile << "std::cerr";
        flux_out_rec(std::forward<All>(all)...);
        this->fluxFile << ";";
    }

    /**
    * Generate a cin
    * @param all: all the elements of the flux
    */
    template <typename... All>
    void _cin(All &&... all)
    {
        this->fluxFile << "std::cin";
        flux_in_rec(std::forward<All>(all)...);
        this->fluxFile << ";";
    }

    /**
    * Generate structure 
    * @param struct_name: name of the structure
    */
    void _struct(std::string struct_name)
    {
        this->fluxFile << "struct " << struct_name << "{";
    }

    /**
    * Generate structure with a typedef
    * @param struct_name: name of the structure
    */
    void _struct_typedef(std::string struct_name)
    {
        this->fluxFile << "typedef struct " << struct_name << " " << struct_name << ";struct " << struct_name << "{";
    }

    /**
    * Generate a class
    * @param class_name: name of the class
    */
    void _class(std::string class_name)
    {
        this->fluxFile << "class " << class_name << "{";
    }

    /**
    * Generate a private section in a class
    */
    void _private()
    {
        this->fluxFile << "private :";
    }

    /**
    * Generate a protected section in a class
    */
    void _protected()
    {
        this->fluxFile << "protected :";
    }

    /**
    * Generate a public section in a class
    */
    void _public()
    {
        this->fluxFile << "public :";
    }

    /**
    * Generate an include
    * @param file: file to include
    */
    void _include(std::string file)
    {
        this->fluxFile << "#include " << file << std::endl;
    }

    /**
    * Generate a define
    * @param obj: object to define
    */
    void _define(std::string obj)
    {
        this->fluxFile << "#define " << obj << std::endl;
    }

    /**
    * Generate an ifndef
    * @param header: header to check
    */
    void _ifndef(std::string header)
    {
        this->fluxFile << "#ifndef " << header << std::endl;
    }

    /**
    * Generate an endif
    */
    void _endif()
    {
        this->fluxFile << "#endif";
    }

    /**
    * Generate a return
    * @param all: all the elements of the return
    */
    template <typename... All>
    void _return(All &&... all)
    {
        this->fluxFile << "return ";
        code_rec(std::forward<All>(all)...);
        this->fluxFile << ";";
    }

    /**
    * Generate an exit
    * @param code: the exit code
    */
    template <typename Code>
    void _exit(Code code)
    {
        this->fluxFile << "exit(" << std::forward<Code>(code) << ")";
    }

    /**
    * Generate an if
    * @param all: all the elements of the if
    */
    template <typename... All>
    void _if(All &&... all)
    {
        this->fluxFile << "if(";
        code_rec(std::forward<All>(all)...);
        this->fluxFile << "){";
    }

    /**
    * Generate a else
    */
    void _else()
    {
        this->fluxFile << "else{";
    }

    /**
    * Generate a for
    * @param all: all the elements of the for
    */
    template <typename... All>
    void _for(All &&... all)
    {
        this->fluxFile << "for(";
        code_rec(std::forward<All>(all)...);
        this->fluxFile << "){";
    }

    /**
    * Generate a do while
    */
    void _do()
    {
        this->fluxFile << "do{";
    }

    /**
    * Generate a while
    * @param all: all the elements of the while
    */
    template <typename... All>
    void _while(All &&... all)
    {
        this->fluxFile << "while(";
        code_rec(std::forward<All>(all)...);
        this->fluxFile << "){";
    }

    /**
    * Generate a switch
    * @param all: all the elements of the switch
    */
    template <typename... All>
    void _switch(All &&... all)
    {
        this->fluxFile << "switch(";
        code_rec(std::forward<All>(all)...);
        this->fluxFile << "){";
    }

    /**
    * Generate a case in a switch
    * @param all: all the elements of the case
    */
    template <typename... All>
    void _case(All &&... all)
    {
        this->fluxFile << "case";
        code_rec(std::forward<All>(all)...);
        this->fluxFile << ":";
    }

    /**
    * Generate a default in a switch
    */
    void _default()
    {
        this->fluxFile << "default:";
    }

    /**
    * Generate a break
    */
    void _break()
    {
        this->fluxFile << "break;";
    }

    /**
    * Generate a try
    */
    void _try()
    {
        this->fluxFile << "try{";
    }

    /**
    * Generate a catch
    * @param rest: all the elements of the catch
    */
    template <typename... All>
    void _catch(All &&... all)
    {
        this->fluxFile << "catch(";
        code_rec(std::forward<All>(all)...);
        this->fluxFile << "){";
    }
    
    /**
    * Generate a comment
    * @param rest: all the elements of the comment
    */
    template <typename... All>
    void _comment(All &&... all)
    {
        this->fluxFile << "/*";
        code_rec(std::forward<All>(all)...);
        this->fluxFile << "*/";
    }

    /**
    * Generate a comment in one line
    * @param rest: all the elements of the comment
    */
    template <typename... All>
    void _comment_line(All &&... all)
    {
        this->fluxFile << "/*//";
        code_rec(std::forward<All>(all)...);
        this->fluxFile << "*/";
    }
};

#endif
