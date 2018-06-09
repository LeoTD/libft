/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltanenba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 22:23:39 by ltanenba          #+#    #+#             */
/*   Updated: 2018/06/08 07:07:28 by ltanenba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_prompt.h"

int				term_init(t_term *t)
{
	t->name = getenv("TERM");
	t->fd = open("/dev/tty", O_RDWR);
	tgetent(0, t->name);
	tcgetattr(STDIN_FILENO, &t->normal);
	tcgetattr(STDIN_FILENO, &t->custom);
	t->custom.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	t->custom.c_oflag &= ~(OPOST);
	t->custom.c_cflag |= CS8;
	t->custom.c_lflag &= ~(ICANON | ECHO | IEXTEN | ISIG);
	t->custom.c_cc[VMIN] = 1;
	t->custom.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &t->custom);
	return (0);
}

size_t			get_cols(void)
{
	struct winsize		w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return (w.ws_col);
}

int				prompt_init(t_prompt *p, char *pstr)
{
	p->ifd = STDIN_FILENO;
	p->ofd = STDOUT_FILENO;
	p->pstr = pstr;
	p->plen = ft_strlen(pstr);
	MALL_CHECK(p->buf = ft_strnew(LINE_START_SIZE));
	p->buf_size = LINE_START_SIZE;
	p->len = 0;
	p->cols = get_cols();
	p->pos = 0;
	return (0);
}

int				ft_weirdchar(int c)
{
	write(STDOUT_FILENO, &c, 1);
	return (0);
}
