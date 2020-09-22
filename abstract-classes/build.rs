use cc;


fn main() {
   cc::Build::new()
       .cpp(true)
       .include("cpp_sources")
       .file("cpp_sources/Engine.cpp")
       .file("cpp_sources/bindings.cpp")
       .flag("/EHsc")
       .warnings_into_errors(true)
       .compile("logger");
}