// Distributed under the MIT License.
// See LICENSE.txt for details.

#include "tests/Unit/TestingFramework.hpp"

#include <cstddef>

#include "DataStructures/DataVector.hpp"
#include "DataStructures/Matrix.hpp"
#include "NumericalAlgorithms/Spectral/Spectral.hpp"

namespace {

void test_points_and_weights(const size_t num_points,
                             const DataVector expected_points,
                             const DataVector expected_weights) {
  const auto& points =
      Spectral::collocation_points<Spectral::Basis::Legendre,
                                   Spectral::Quadrature::GaussLobatto>(
          num_points);
  CHECK_ITERABLE_APPROX(expected_points, points);
  const auto& weights =
      Spectral::quadrature_weights<Spectral::Basis::Legendre,
                                   Spectral::Quadrature::GaussLobatto>(
          num_points);
  CHECK_ITERABLE_APPROX(expected_weights, weights);
}

}  // namespace

SPECTRE_TEST_CASE(
    "Unit.Numerical.Spectral.LegendreGaussLobatto.PointsAndWeights",
    "[NumericalAlgorithms][Spectral][Unit]") {
  // Compare LGL points to Matlab code accompanying the
  // book "Nodal Discontinuous Galerkin Methods" by Hesthaven and Warburton
  // available at http://www.nudg.org/. To compute `num_points` LGL points, run
  // the routine `JacobiGL(0, 0, num_points - 1)`.
  // Quadrature weights computed in Mathematica, code available on request from
  // nils.fischer@aei.mpg.de.

  SECTION("Check 2 points") {
    test_points_and_weights(2, DataVector{-1.0, 1.0}, DataVector{1.0, 1.0});
  }
  SECTION("Check 3 points") {
    test_points_and_weights(3, DataVector{-1.0, 0.0, 1.0},
                            DataVector{1.0, 4.0, 1.0} / 3.0);
  }
  SECTION("Check 4 points") {
    test_points_and_weights(
        4, DataVector{-1.0, -0.4472135954999579, 0.4472135954999579, 1.0},
        DataVector{1.0, 5.0, 5.0, 1.0} / 6.0);
  }
  SECTION("Check 5 points") {
    test_points_and_weights(
        5, DataVector{-1.0, -0.6546536707079773, 0.0, 0.6546536707079773, 1.0},
        DataVector{9.0, 49.0, 64.0, 49.0, 9.0} / 90.0);
  }
  SECTION("Check 6 points") {
    test_points_and_weights(
        6,
        DataVector{-1.0, -0.7650553239294646, -0.2852315164806452,
                   0.2852315164806452, 0.7650553239294646, 1.0},
        DataVector{1.0 / 15.0, 0.378474956297847, 0.554858377035486,
                   0.554858377035486, 0.378474956297847, 1.0 / 15.0});
  }
  SECTION("Check 7 points") {
    test_points_and_weights(
        7,
        DataVector{-1.0, -0.8302238962785669, -0.4688487934707142, 0.0,
                   0.4688487934707142, 0.8302238962785669, 1.0},
        DataVector{1.0 / 21.0, 0.276826047361566, 0.431745381209860,
                   0.487619047619048, 0.431745381209862, 0.276826047361567,
                   1.0 / 21.0});
  }
  SECTION("Check 8 points") {
    test_points_and_weights(
        8,
        DataVector{-1.0, -0.8717401485096066, -0.5917001814331421,
                   -0.2092992179024791, 0.2092992179024791, 0.5917001814331421,
                   0.8717401485096066, 1.0},
        DataVector{1.0 / 28.0, 0.210704227143507, 0.341122692483504,
                   0.412458794658705, 0.412458794658705, 0.341122692483504,
                   0.210704227143507, 1.0 / 28.0});
  }
  SECTION("Check 9 points") {
    test_points_and_weights(
        9,
        DataVector{-1.0, -0.8997579954114600, -0.6771862795107377,
                   -0.3631174638261783, 0.0, 0.3631174638261783,
                   0.6771862795107377, 0.8997579954114600, 1.0},
        DataVector{1.0 / 36.0, 0.165495361560806, 0.274538712500161,
                   0.346428510973042, 0.371519274376423, 0.346428510973042,
                   0.274538712500161, 0.165495361560806, 1.0 / 36.0});
  }
  SECTION("Check 10 points") {
    test_points_and_weights(
        10,
        DataVector{-1.0, -0.9195339081664589, -0.7387738651055048,
                   -0.4779249498104444, -0.1652789576663869, 0.1652789576663869,
                   0.4779249498104444, 0.7387738651055048, 0.9195339081664589,
                   1.0},
        DataVector{1.0 / 45.0, 0.133305990851069, 0.224889342063126,
                   0.292042683679679, 0.327539761183898, 0.327539761183898,
                   0.292042683679680, 0.224889342063126, 0.133305990851071,
                   1.0 / 45.0});
  }
  if (Spectral::maximum_number_of_points<Spectral::Basis::Legendre> >= 20) {
    SECTION("Check 20 points") {
      test_points_and_weights(
          20,
          DataVector{-1.0,
                     -0.0805459372388217,
                     -0.2395517059229869,
                     -0.3923531837139090,
                     -0.5349928640318858,
                     -0.6637764022903113,
                     -0.7753682609520557,
                     -0.8668779780899503,
                     -0.9359344988126655,
                     -0.9807437048939139,
                     0.08054593723882171,
                     0.2395517059229869,
                     0.3923531837139090,
                     0.5349928640318858,
                     0.6637764022903113,
                     0.7753682609520557,
                     0.8668779780899503,
                     0.9359344988126655,
                     0.9807437048939139,
                     1.0},
          DataVector{1.0 / 190.0,        0.160743286387015,  0.156580102645661,
                     0.148361554072526,  0.136300482360142,  0.120709227630445,
                     0.101991499698685,  0.0806317640010999, 0.0571818021276912,
                     0.0322371231888077, 0.160743286386819,  0.156580102645406,
                     0.148361554071531,  0.136300482358238,  0.120709227630445,
                     0.101991499698478,  0.0806317639996452, 0.0571818021277683,
                     0.0322371231896326, 1.0 / 190.0});
    }
  }
}

namespace {

void test_diff_matrix(const size_t num_points, const Matrix& expected_matrix) {
  const auto& diff_matrix =
      Spectral::differentiation_matrix<Spectral::Basis::Legendre,
                                       Spectral::Quadrature::GaussLobatto>(
          num_points);
  CHECK_MATRIX_APPROX(expected_matrix, diff_matrix);
}

}  // namespace

SPECTRE_TEST_CASE("Unit.Numerical.Spectral.LegendreGaussLobatto.DiffMatrix",
                  "[NumericalAlgorithms][Spectral][Unit]") {
  // Compare differentiation matrix values to matlab code accompanying the
  // book "Nodal Discontinuous Galerkin Methods" by Hesthaven and Warburton
  // available at http://www.nudg.org/.
  //
  // Command to generate differentation matrix with the Matlab code:
  // DN = Dmatrix1D(N, JacobiGL(0,0,N), Vandermonde1D(N, JacobiGL(0,0,N)))

  SECTION("Check 2 points") {
    test_diff_matrix(2, Matrix({{-0.5, 0.5}, {-0.5, 0.5}}));
  }

  SECTION("Check 3 points") {
    test_diff_matrix(
        3, Matrix({{-1.5, 2., -0.5}, {-0.5, 0., 0.5}, {0.5, -2., 1.5}}));
  }

  SECTION("Check 4 points") {
    test_diff_matrix(
        4,
        Matrix({{-3., 4.04508497187474, -1.54508497187474, 0.5},
                {-0.809016994374947, 0., 1.11803398874990, -0.309016994374947},
                {0.309016994374947, -1.11803398874990, 0., 0.809016994374947},
                {-0.5, 1.54508497187474, -4.04508497187474, 3.}}));
  }

  SECTION("Check 5 points") {
    test_diff_matrix(
        5, Matrix({{-5., 6.75650248872424, -2.66666666666666, 1.41016417794243,
                    -0.5},
                   {-1.24099025303098, 0., 1.74574312188794, -0.763762615825973,
                    0.259009746969017},
                   {0.375, -1.33658457769545, 0., 1.33658457769545, -0.375},
                   {-0.259009746969017, 0.763762615825973, -1.74574312188794,
                    0., 1.24099025303098},
                   {0.5, -1.41016417794243, 2.66666666666666, -6.75650248872424,
                    5.}}));
  }

  SECTION("Check 6 points") {
    test_diff_matrix(
        6, Matrix({{-7.5, 10.1414159363197, -4.03618727030535, 2.24468464817617,
                    -1.34991331419049, 0.5},
                   {-1.78636494833909, 0., 2.52342677742946, -1.15282815853593,
                    0.653547507429800, -0.237781177984231},
                   {0.484951047853569, -1.72125695283023, 0., 1.75296196636787,
                    -0.786356672223241, 0.269700610832039},
                   {-0.269700610832039, 0.786356672223241, -1.75296196636787,
                    0., 1.72125695283023, -0.484951047853569},
                   {0.237781177984231, -0.653547507429800, 1.15282815853593,
                    -2.52342677742946, 0., 1.78636494833909},
                   {-0.5, 1.34991331419049, -2.24468464817617, 4.03618727030535,
                    -10.1414159363197, 7.5}}));
  }

  SECTION("Check 10 points") {
    test_diff_matrix(
        10,
        Matrix({{-22.5, 30.4381450292819, -12.1779467074298, 6.94378848513396,
                 -4.59935476110314, 3.29464303374919, -2.45288417544269,
                 1.82956393190325, -1.27595483609266, 0.5},
                {-5.07406470297807, 1.90958360235527e-14, 7.18550286970582,
                 -3.35166386274678, 2.07820799403642, -1.44494844875146,
                 1.05915446364544, -0.783239293137909, 0.543753738235705,
                 -0.212702758009189},
                {1.20335199285221, -4.25929735496521, -1.95399252334028e-14,
                 4.36867455701019, -2.10435017941316, 1.33491548387825,
                 -0.936603213139449, 0.676797087196086, -0.464274958908157,
                 0.180786585489250},
                {-0.528369376820272, 1.52990263818160, -3.36412586829782, 0.,
                 3.38731810120245, -1.64649408398706, 1.04618936550249,
                 -0.721237312721603, 0.483462326333947, -0.186645789393736},
                {0.312047255608411, -0.845813573406423, 1.44485031560166,
                 -3.02021795819935, 0., 3.02518848775198, -1.46805550938999,
                 0.916555180336434, -0.588082143045168, 0.223527944742453},
                {-0.223527944742453, 0.588082143045168, -0.916555180336434,
                 1.46805550938999, -3.02518848775198, 0., 3.02021795819935,
                 -1.44485031560166, 0.845813573406422, -0.312047255608411},
                {0.186645789393736, -0.483462326333947, 0.721237312721603,
                 -1.04618936550249, 1.64649408398706, -3.38731810120245, 0.,
                 3.36412586829782, -1.52990263818160, 0.528369376820272},
                {-0.180786585489250, 0.464274958908157, -0.676797087196086,
                 0.936603213139449, -1.33491548387825, 2.10435017941316,
                 -4.36867455701019, 1.95399252334028e-14, 4.25929735496520,
                 -1.20335199285221},
                {0.212702758009189, -0.543753738235706, 0.783239293137910,
                 -1.05915446364544, 1.44494844875146, -2.07820799403642,
                 3.35166386274678, -7.18550286970582, -1.90958360235527e-14,
                 5.07406470297807},
                {-0.5, 1.27595483609266, -1.82956393190325, 2.45288417544269,
                 -3.29464303374919, 4.59935476110314, -6.94378848513396,
                 12.1779467074298, -30.4381450292819, 22.5}}));
  }
}

namespace {

void test_spectral_to_grid_points_matrix(const size_t num_points,
                                         const Matrix& expected_matrix) {
  const auto& matrix = Spectral::spectral_to_grid_points_matrix<
      Spectral::Basis::Legendre, Spectral::Quadrature::GaussLobatto>(
      num_points);
  CHECK_MATRIX_APPROX(expected_matrix, matrix);
}

}  // namespace

SPECTRE_TEST_CASE(
    "Unit.Numerical.Spectral.LegendreGaussLobatto.SpectralToGridPoints",
    "[NumericalAlgorithms][Spectral][Unit]") {
  SECTION("Check 2 points") {
    test_spectral_to_grid_points_matrix(2, Matrix({{1., -1.}, {1., 1.}}));
  }
  SECTION("Check 3 points") {
    test_spectral_to_grid_points_matrix(
        3, Matrix({{1., -1., 1.}, {1., 0., -0.5}, {1., 1., 1.}}));
  }
  SECTION("Check 4 points") {
    test_spectral_to_grid_points_matrix(
        4, Matrix({{1., -1., 1., -1.},
                   {1., -0.4472135954999579, -0.2, 0.4472135954999580},
                   {1., 0.4472135954999579, -0.2, -0.4472135954999580},
                   {1., 1., 1., 1.}}));
  }
  SECTION("Check 5 points") {
    test_spectral_to_grid_points_matrix(
        5, Matrix({{1., -1., 1., -1., 1.},
                   {1., -0.6546536707079772, 0.1428571428571430,
                    0.2805658588748472, -0.4285714285714287},
                   {1., 0, -0.4999999999999999, 0, 0.3749999999999999},
                   {1., 0.6546536707079772, 0.1428571428571430,
                    -0.2805658588748472, -0.4285714285714287},
                   {1., 1., 1., 1., 1.}}));
  }
  SECTION("Check 6 points") {
    test_spectral_to_grid_points_matrix(
        6,
        Matrix(
            {{1., -1., 1., -1., 1., -1.},
             {1., -0.7650553239294646, 0.3779644730092270, 0.02809732873313717,
              -0.3210913738940153, 0.4196969341312872},
             {1., -0.2852315164806452, -0.3779644730092271, 0.3698333106741464,
              0.09886915167179271, -0.3466277250554177},
             {1., 0.2852315164806452, -0.3779644730092271, -0.3698333106741464,
              0.09886915167179271, 0.3466277250554177},
             {1., 0.7650553239294646, 0.3779644730092270, -0.02809732873313717,
              -0.3210913738940153, -0.4196969341312872},
             {1., 1., 1., 1., 1., 1.}}));
  }
  SECTION("Check 10 points") {
    test_spectral_to_grid_points_matrix(
        10,
        Matrix(
            {{1., -1., 1., -1., 1., -1., 1., -1., 1., -1.},
             {1., -0.9195339081664589, 0.7683139124018223, -0.5644618855048774,
              0.3320877919799225, -0.09808926498070079, -0.1113797504923236,
              0.2742803620392504, -0.3754366431428354, 0.4082901563591628},
             {1., -0.7387738651055048, 0.3186802356443899, 0.1001281943707717,
              -0.3684613397656203, 0.4098747391204626, -0.2480909164487299,
              -0.01093833236737723, 0.2322313407942435, -0.3143469900103700},
             {1., -0.4779249498104444, -0.1573816135230263, 0.4439776327804282,
              -0.2532927686189359, -0.1372832255111463, 0.3313642847298692,
              -0.1764392879805111, -0.1318348656648675, 0.2758484689220680},
             {1., -0.1652789576663869, -0.4590242992290690, 0.2366310679777983,
              0.2758254859548065, -0.2713635222518218, -0.1476283247671612,
              0.2779113224035852, 0.04305060850148148, -0.2604724104587964},
             {1., 0.1652789576663869, -0.4590242992290690, -0.2366310679777983,
              0.2758254859548065, 0.2713635222518218, -0.1476283247671612,
              -0.2779113224035852, 0.04305060850148148, 0.2604724104587964},
             {1., 0.4779249498104444, -0.1573816135230263, -0.4439776327804282,
              -0.2532927686189359, 0.1372832255111463, 0.3313642847298692,
              0.1764392879805111, -0.1318348656648675, -0.2758484689220680},
             {1., 0.7387738651055048, 0.3186802356443899, -0.1001281943707717,
              -0.3684613397656203, -0.4098747391204626, -0.2480909164487299,
              0.01093833236737723, 0.2322313407942435, 0.3143469900103700},
             {1., 0.9195339081664589, 0.7683139124018223, 0.5644618855048774,
              0.3320877919799225, 0.09808926498070079, -0.1113797504923236,
              -0.2742803620392504, -0.3754366431428354, -0.4082901563591628},
             {1., 1., 1., 1., 1., 1., 1., 1., 1., 1.}}));
  }
}

namespace {

void test_grid_points_to_spectral_matrix(const size_t num_points,
                                         const Matrix& expected_matrix) {
  const auto& matrix = Spectral::grid_points_to_spectral_matrix<
      Spectral::Basis::Legendre, Spectral::Quadrature::GaussLobatto>(
      num_points);
  CHECK_MATRIX_APPROX(expected_matrix, matrix);
}

}  // namespace

SPECTRE_TEST_CASE(
    "Unit.Numerical.Spectral.LegendreGaussLobatto.GridPointsToSpectral",
    "[NumericalAlgorithms][Spectral][Unit]") {
  SECTION("Check 2 points") {
    test_grid_points_to_spectral_matrix(2, Matrix({{0.5, 0.5}, {-0.5, 0.5}}));
  }
  SECTION("Check 3 points") {
    test_grid_points_to_spectral_matrix(3,
                                        Matrix({{1. / 6., 2. / 3., 1. / 6.},
                                                {-1. / 2., 0., 1. / 2.},
                                                {1. / 3., -2. / 3., 1. / 3.}}));
  }
  SECTION("Check 4 points") {
    test_grid_points_to_spectral_matrix(
        4, Matrix({{0.08333333333333320, 0.4166666666666668, 0.4166666666666666,
                    0.08333333333333337},
                   {-0.25, -0.5590169943749476, 0.5590169943749476, 0.25},
                   {0.4166666666666667, -0.4166666666666668,
                    -0.4166666666666666, 0.4166666666666666},
                   {-0.25, 0.5590169943749476, -0.5590169943749476, 0.25}}));
  }
  SECTION("Check 5 points") {
    test_grid_points_to_spectral_matrix(
        5, Matrix({{0.05, 0.2722222222222222, 0.3555555555555557,
                    0.2722222222222221, 0.05},
                   {-0.15, -0.5346338310781814, 0., 0.5346338310781813, 0.15},
                   {0.25, 0.1944444444444444, -0.8888888888888887,
                    0.1944444444444443, 0.25},
                   {-0.35, 0.5346338310781814, 0., -0.5346338310781813, 0.35},
                   {0.2, -0.4666666666666666, 0.5333333333333330,
                    -0.4666666666666665, 0.2}}));
  }
  SECTION("Check 6 points") {
    test_grid_points_to_spectral_matrix(
        6,
        Matrix(
            {{0.03333333333333338, 0.1892374781489234, 0.2774291885177432,
              0.2774291885177432, 0.1892374781489234, 0.03333333333333341},
             {-0.1, -0.4343314204344590, -0.2373946444707316,
              0.2373946444707316, 0.4343314204344590, 0.1},
             {0.1666666666666666, 0.3576252185107653, -0.5242918851774320,
              -0.5242918851774321, 0.3576252185107653, 0.1666666666666667},
             {-0.2333333333333333, 0.03721947342526071, 0.7182178868701115,
              -0.7182178868701115, -0.03721947342526071, 0.2333333333333333},
             {0.2999999999999999, -0.5468626966596887, 0.2468626966596887,
              0.2468626966596888, -0.5468626966596887, 0.2999999999999999},
             {-0.1666666666666666, 0.3971119470091983, -0.4808232423993798,
              0.4808232423993798, -0.3971119470091983, 0.1666666666666666}}));
  }
  SECTION("Check 10 points") {
    test_grid_points_to_spectral_matrix(
        10,
        Matrix(
            {{0.01111111111111113, 0.06665299542553522, 0.1124446710315631,
              0.1460213418398418, 0.1637698805919488, 0.1637698805919487,
              0.1460213418398418, 0.1124446710315632, 0.06665299542553520,
              0.01111111111111101},
             {-0.03333333333333321, -0.1838690681239303, -0.2492135526855150,
              -0.2093617274101802, -0.08120314548415815, 0.08120314548415815,
              0.2093617274101802, 0.2492135526855150, 0.1838690681239303,
              0.03333333333333320},
             {0.05555555555555547, 0.2560521184434683, 0.1791694713064728,
              -0.1149053719377589, -0.3758717733677376, -0.3758717733677376,
              -0.1149053719377588, 0.1791694713064727, 0.2560521184434683,
              0.05555555555555547},
             {-0.07777777777777778, -0.2633615283071183, 0.07881217313904033,
              0.4538114677983227, 0.2712712922294855, -0.2712712922294855,
              -0.4538114677983228, -0.07881217313904021, 0.2633615283071183,
              0.07777777777777772},
             {0.1, 0.1992118147174238, -0.3728836272401474, -0.3328753495685899,
              0.4065471620913135, 0.4065471620913135, -0.3328753495685899,
              -0.3728836272401475, 0.1992118147174238, 0.1},
             {-0.1222222222222223, -0.07191737663057941, 0.5069705322500303,
              -0.2205090888136316, -0.4888528879981061, 0.4888528879981059,
              0.2205090888136318, -0.5069705322500304, 0.07191737663057941,
              0.1222222222222224},
             {0.1444444444444446, -0.09650932200080796, -0.3626545193179547,
              0.6290213474227139, -0.3143019505483959, -0.3143019505483958,
              0.6290213474227141, -0.3626545193179548, -0.09650932200080796,
              0.1444444444444446},
             {-0.1666666666666666, 0.2742241157447441, -0.01844935777025255,
              -0.3864585237627080, 0.6827025612777864, -0.6827025612777864,
              0.3864585237627079, 0.01844935777025254, -0.2742241157447441,
              0.1666666666666667},
             {0.1888888888888889, -0.4254076065856193, 0.4439240042200661,
              -0.3272619677562069, 0.1198566812328714, 0.1198566812328711,
              -0.3272619677562070, 0.4439240042200662, -0.4254076065856192,
              0.1888888888888887},
             {-0.1, 0.2449238573168839, -0.3181197949333031, 0.3625178721881970,
              -0.3839178200250077, 0.3839178200250077, -0.3625178721881971,
              0.3181197949333031, -0.2449238573168839, 0.1}}));
  }
}
