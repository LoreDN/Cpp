# ======================== General Build Rule ========================
.PHONY: all Exception clean

all: Exception


# ===================== Exception/CMakeLists.txt =====================
Exception:
	mkdir -p build/Exception/temp
	cmake -S build/Exception -B build/Exception/temp -DCMAKE_INSTALL_PREFIX=/usr
	cmake --build build/Exception/temp --target package_exception
	rm -rf build/Exception/temp

doc-Exception:
	pdflatex -output-directory=docs/Exception/v1.0.0 docs/Exception/v1.0.0/Exception.tex
	pdflatex -output-directory=docs/Exception/v1.0.0 docs/Exception/v1.0.0/Exception.tex
	rm -f docs/Exception/v1.0.0/Exception.aux docs/Exception/v1.0.0/Exception.log 
	rm -f docs/Exception/v1.0.0/Exception.out docs/Exception/v1.0.0/Exception.toc

uml-Exception:
	plantuml -tpdf docs/Exception/v1.0.0/Exception_UML.puml


# ======================== Hash/CMakeLists.txt =======================
doc-Hash:
	pdflatex -output-directory=docs/Hash/v1.0.0 docs/Hash/v1.0.0/Hash.tex
	pdflatex -output-directory=docs/Hash/v1.0.0 docs/Hash/v1.0.0/Hash.tex
	rm -f docs/Hash/v1.0.0/Hash.aux docs/Hash/v1.0.0/Hash.log 
	rm -f docs/Hash/v1.0.0/Hash.out docs/Hash/v1.0.0/Hash.toc

uml-Hash:
	plantuml -tpdf docs/Hash/v1.0.0/Hash_UML.puml


# =================== Clean Rule --- build/lib/temp ==================
clean:
	rm -rf build/*/temp