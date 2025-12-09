# ======================== General Build Rule ========================
.PHONY: all Exception Hash clean

all: Exception Hash


# ===================== Exception/CMakeLists.txt =====================
Exception:
	mkdir -p build
	cmake -S include/LDN/Exception -B build -DCMAKE_INSTALL_PREFIX=/usr
	cmake --build build --target package_exception
	rm -rf build

doc-Exception:
	pdflatex -output-directory=docs/Exception/v1.0 docs/Exception/v1.0/Exception.tex
	pdflatex -output-directory=docs/Exception/v1.0 docs/Exception/v1.0/Exception.tex
	rm -f docs/Exception/v1.0/Exception.aux docs/Exception/v1.0/Exception.log 
	rm -f docs/Exception/v1.0/Exception.out docs/Exception/v1.0/Exception.toc

uml-Exception:
	plantuml -tpdf docs/Exception/v1.0/Exception_UML.puml


# ======================== Hash/CMakeLists.txt =======================
Hash:
	mkdir -p build
	cmake -S include/LDN/Hash -B build -DCMAKE_INSTALL_PREFIX=/usr
	cmake --build build --target package_hash
	rm -rf build

doc-Hash:
	pdflatex -output-directory=docs/Hash/v1.0.0 docs/Hash/v1.0.0/Hash.tex
	pdflatex -output-directory=docs/Hash/v1.0.0 docs/Hash/v1.0.0/Hash.tex
	rm -f docs/Hash/v1.0.0/Hash.aux docs/Hash/v1.0.0/Hash.log 
	rm -f docs/Hash/v1.0.0/Hash.out docs/Hash/v1.0.0/Hash.toc

uml-Hash:
	plantuml -tpdf docs/Hash/v1.0.0/Hash_UML.puml


# =================== Clean Rule --- build/lib/temp ==================
clean:
	rm -rf include/LDN/*/build