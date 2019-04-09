/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emartine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 16:35:35 by emartine          #+#    #+#             */
/*   Updated: 2019/03/30 16:35:37 by emartine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "twenty_one_sh.h"
#include "lexer_internal.h"

static inline void	lexer_debug_tokens(t_lexer *lex)
{
	t_lexer_token	*cur;

	if (lex->head)
	{
		cur = lex->head;
		while (cur)
		{
			printer_str(&g_shell.out, "token=");
			printer_int(&g_shell.out, (int)cur->type);
			printer_str(&g_shell.out, " line_y=");
			printer_ulong(&g_shell.out, cur->line_y);
			printer_str(&g_shell.out, " line_x=");
			printer_ulong(&g_shell.out, cur->line_x);
			printer_str(&g_shell.out, " size=");
			printer_ulong(&g_shell.out, cur->size);
			printer_str(&g_shell.out, " buf='");
			printer_bin(&g_shell.out, cur->buffer, cur->size);
			printer_str(&g_shell.out, "'");
			printer_endl(&g_shell.out);
			cur = cur->next;
		}
	}
}

void				lexer_debug(t_lexer *lex)
{
	if (!g_shell.debug_mode)
		return ;
	printer_str(&g_shell.out, "lexer_debug:\nbs=");
	printer_int(&g_shell.out, lex->backslash_newline);
	printer_str(&g_shell.out, " qu=");
	printer_int(&g_shell.out, lex->quoted);
	printer_str(&g_shell.out, " nq=");
	printer_int(&g_shell.out, lex->next_quoted);
	printer_str(&g_shell.out, " es=");
	printer_ulong(&g_shell.out, lex->expansion_size);
	printer_endl(&g_shell.out);
	lexer_debug_tokens(lex);
	printer_flush(&g_shell.out);
}
