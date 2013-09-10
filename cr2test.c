#include "raw.c"

void write_file(const char* path, const char* data, int len) {
	FILE* ofp = fopen(path, "wb");
	fwrite(data, 1, len, ofp);
	fclose(ofp);
	printf("Written %s\n", path);
}

int main(int argc, char* argv[]) {
   	struct img_data img;
	int fd = open(argv[1], O_RDONLY);
    if (fd != -1) {
        prepare_jpeg(fd, &img);
       	write_file("thumb_exif.jpg", img.out, img.out_length);
    	free(img.out);

		printf("thumb_offset 0x%x, thumb_length %d, exif_offset %d\n", img.thumb_offset, img.thumb_length, img.exif_offset);
		
		lseek(fd, img.thumb_offset, SEEK_SET);
		char *thumb = malloc(img.thumb_length);
		read(fd, thumb, img.thumb_length);
		
		write_file("thumb.jpg", thumb, img.thumb_length);
		close(fd);
    }
    return 0;
}

