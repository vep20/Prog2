#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_opengl.h>

int main(void)
{
  al_init();
  al_set_new_display_flags(ALLEGRO_OPENGL);
  ALLEGRO_DISPLAY *display = al_create_display(800, 600);
  al_clear_to_color(al_map_rgb(0, 0, 0));
  al_init_image_addon();

  if (!al_init_image_addon()){
    printf("Falha ao inicializar add-on allegro_image.\n");
    return -1;
  }

  ALLEGRO_BITMAP *img = al_load_bitmap("teste.png");
  al_draw_bitmap(img, 10, 10, 0);
  al_flip_display();
  al_rest(5);
  al_destroy_bitmap(img);
  
  return 0;
}