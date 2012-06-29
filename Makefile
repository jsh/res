default: res

clean:
	rm -f $$(cat .gitignore)

fmt:
	indent -linux *.c

.PHONY: clean default
.SILENT:
