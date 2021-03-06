#ifndef MAMBA_SOLVER_HPP
#define MAMBA_SOLVER_HPP

#include <vector>
#include <utility>
#include <string>
#include <sstream>

#include "pool.hpp"
#include "output.hpp"

extern "C"
{
    #include "solv/queue.h"
    #include "solv/conda.h"
    #include "solv/solver.h"
    #include "solv/solverdebug.h"
}

namespace mamba
{
    class MSolver
    {
    public:

        MSolver(MPool& pool, const std::vector<std::pair<int, int>>& flags = {});
        ~MSolver();

        MSolver(const MSolver&) = delete;
        MSolver& operator=(const MSolver&) = delete;
        MSolver(MSolver&&) = delete;
        MSolver& operator=(MSolver&&) = delete;

        void add_jobs(const std::vector<std::string>& jobs, int job_flag);
        void set_flags(const std::vector<std::pair<int, int>>& flags);
        bool is_solved();
        bool solve();
        std::string problems_to_str();

        const std::vector<std::string>& install_specs() const;
        const std::vector<std::string>& remove_specs() const;

        operator Solver*();

    private:

        std::vector<std::string> m_install_specs;
        std::vector<std::string> m_remove_specs;
        std::vector<std::string> m_neuter_specs; // unused for now
        bool m_is_solved;
        Solver* m_solver;
        Queue m_jobs;
    };
}

#endif // MAMBA_SOLVER_HPP
