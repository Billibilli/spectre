// Distributed under the MIT License.
// See LICENSE.txt for details.

#include "tests/Unit/TestingFramework.hpp"

#include <cstddef>
#include <tuple>

#include "DataStructures/DataBox/Prefixes.hpp"  // IWYU pragma: keep
#include "DataStructures/DataVector.hpp"
#include "Elliptic/Systems/Poisson/Tags.hpp"  // IWYU pragma: keep
#include "PointwiseFunctions/AnalyticSolutions/Poisson/Moustache.hpp"
#include "Utilities/TMPL.hpp"
#include "tests/Unit/Pypp/CheckWithRandomValues.hpp"
#include "tests/Unit/Pypp/SetupLocalPythonEnvironment.hpp"
#include "tests/Unit/TestCreation.hpp"
#include "tests/Unit/TestHelpers.hpp"

namespace {

template <size_t Dim>
void test_solution() {
  const Poisson::Solutions::Moustache<Dim> solution{};
  pypp::check_with_random_values<
      1, tmpl::list<Poisson::Field, Poisson::AuxiliaryField<Dim>>>(
      &Poisson::Solutions::Moustache<Dim>::field_variables, solution,
      "Moustache", {"field", "auxiliary_field"}, {{{0., 1.}}},
      std::make_tuple(), DataVector(5));
  pypp::check_with_random_values<
      1, tmpl::list<Tags::Source<Poisson::Field>,
                    Tags::Source<Poisson::AuxiliaryField<Dim>>>>(
      &Poisson::Solutions::Moustache<Dim>::source_variables, solution,
      "Moustache", {"source", "auxiliary_source"}, {{{0., 1.}}},
      std::make_tuple(), DataVector(5));

  Poisson::Solutions::Moustache<Dim> created_solution =
      test_creation<Poisson::Solutions::Moustache<Dim>>("  ");
  CHECK(created_solution == solution);
  test_serialization(solution);
}

}  // namespace

SPECTRE_TEST_CASE("Unit.PointwiseFunctions.AnalyticSolutions.Poisson.Moustache",
                  "[PointwiseFunctions][Unit]") {
  pypp::SetupLocalPythonEnvironment local_python_env{
      "PointwiseFunctions/AnalyticSolutions/Poisson"};
  test_solution<1>();
  test_solution<2>();
}
