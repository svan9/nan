#ifndef BINARY_PACKER_HPP
#define BINARY_PACKER_HPP

#ifndef ZPIPE_H
#define ZPIPE_H
#define SET_BINARY_MODE(file)
#endif
#include <iostream>
#include <cstring>
#include <cassert>
#include "zlib.h"
#include "mewall.h"
#include <initializer_list>


namespace BinaryPack {	
	struct FileContext {
		const char* filename;
		size_t size;
		const char* content;
	};

	struct FolderContext {
		size_t size;
		FileContext* files;
	};

	struct CompressedData {
		size_t compress_factor = 4;
		size_t size;
		byte* data;
	};
	
	struct PackContext {
		mew::stack<FileContext> files;	
	};

	CompressedData pack(const char* str) {
		uLongf compressedSize = compressBound(strlen(str));
    Bytef* compressedData = new Bytef[compressedSize];
		MewAssert(compress(compressedData, &compressedSize, (const Bytef*)str, strlen(str)) == Z_OK);
		CompressedData __cdd;
		__cdd.size = compressedSize;
		__cdd.data = compressedData;
		return __cdd;
	}

	FileContext create_file_ctx(std::filesystem::path path) {
		FileContext ctx;
		ctx.filename = mew::get_file_name(path);	
		auto cdd = pack(mew::ReadFullFile(path));
		ctx.size = cdd.size;
		ctx.content = (const char*)cdd.data;
		return ctx;
	}

	FileContext create_file_ctx(const char* filename) {
		return create_file_ctx(mew::get_path(filename));
	}

	const char* unpack(CompressedData& cdd) {
		uLongf decompressedSize = cdd.size*4;
		Bytef* decompressedData = new Bytef[decompressedSize];
		MewAssert(uncompress(decompressedData, &decompressedSize, cdd.data, cdd.size) == Z_OK);
		return (const char*)decompressedData;
	}

	const char* unpack(byte* data, size_t size) {
		uLongf decompressedSize = size*4;
		Bytef* decompressedData = new Bytef[decompressedSize+1];
		MewAssert(uncompress(decompressedData, &decompressedSize, data, size) == Z_OK);
		decompressedData[decompressedSize] = '\0';
		return (const char*)decompressedData;
	}
	
	void pack(std::initializer_list<const char*> pathes, const char* outpath) {
		std::ofstream file(outpath, std::ios::out | std::ios::binary);
		mew::writeBytes(file, (int)pathes.size());
		MewAssert(file.is_open());
		for (auto& path : pathes) {
			FileContext ctx = create_file_ctx(path);
			mew::writeString(file, ctx.filename);
			mew::writeBytes(file, ctx.size, sizeof(ctx.size));
			mew::writeSeqBytes(file, ctx.content, ctx.size);
		}
	}
	
	FolderContext unpack(const char* archive_path) {
		std::ifstream file(archive_path, std::ios::in | std::ios::binary);
		MewAssert(file.is_open());
		file >> std::noskipws;
		int size = mew::readInt4Bytes(file);
		FolderContext ctx;
		ctx.size = size;
		ctx.files = new FileContext[size];
		for (int i = 0; i < size; ++i) {
			FileContext& fctx = ctx.files[i];
			fctx.filename = mew::ReadString(file);
			mew::readBytes(file, fctx.size);
			mew::readBytes(file, fctx.size);
			mew::readSeqBytes(file, fctx.content, fctx.size);
			fctx.content = unpack((byte*)fctx.content, fctx.size);
			fctx.size = strlen(fctx.content);
		}
		return ctx;
	}
}

#endif