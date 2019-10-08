
=================================Test case===============================
####General Explanation####

We know that when the players are prompted make decision i.e. call, check, fold, raise There are two senarios:

1. if the player's bet is equal to the highest bet, the player can only check or raise
because it would not make sense to fold because the player would only gain with the highest bet but nothing more to lose.
The player also cannot call because he/she is the highest already.
2. If the player's current bet is less than the highest, he/she can call, fold, or raise
The player cannot check because the bet is less than the highest bet.
Additionally, when the player want to call or raise but he/she does not have enough chips (but need to have more than 0),
he/she can still call or raise paying all the chips he/she has. However, in the following turns, the player can no longer 
take action but still remain in the game until this round ends. This player can choose to refill chips to 20 after this round
or quit the game.

Note about Co-winners: Technically for one deck of cards, there cannot be co-winners since we take the suit into account.
However, we made a function in after_round to find equal winners and award them in case that the test case is more than one
deck of cards

We tried all the check, call, fold, raise commands in each round of the game.
if the game ends with 2 or more players. It successfually rank the players and award the winner with winNum +1 and
all chips bet to the common pot is given to the winner(s)
And the game is able to go to next round after all players except one folds.
Players are able to raise one or two chips continuously until ran out of chips.
Players are successfully added and removed
When rejoin, newly joined, or current player have no chips, they are prompted and
ask for refilling back up to 20 chips.

####FIVE CARD DRAW####

We know that 
1)at the beginning of each phase, players have the chance to either bet or check.
2)after the first player who checks, the following players can only raise, call or fold
	a)condition when player don't have enough money to raise/call. players will all in and be silent, considered as by-sider of this round, until the end of the round. their hands will
still be considered when ranking for winner.
		*silent players will be skipped for prompting. but the one will be considered for ranking at last and has the chance of winning.
		*when all other players all in and are silent for the round, the only one player left will have the 
choice to either raise one more time, or fold his cards.
	b)condition when all other players but one have fold, the round will stop and the one will automatically be the winner.
		*fold players will be skipped for any prompting and will not considered in the ranking at last.
		*fold players chips will be deducted as the amount when folded. and those chips will be added to the common pot
		*
	c)condition when all players check, no one bet anything in the first phase, the game will automatically go to the second phase. And if that happens at phase two, round will sort 
all hands directly.
3)the condition to go to the next betting phase is to have everyone still on board(not folded, not silent) have the same number of bet.

in order to implement those functions, we considered different paths the player can run into, and tested them with various conditions.


	
####SEVENCARDSTUD#####

There are 5 turns for players to bet.
After all bettings, bestFive function takes in a orignal hand of 7 cards and return the best 5 cards combination Hand.
(The Hand of 5 cards is the combination of highest ranked 5 cards with the largest each index as possible)
A special version of poker_rank named "poker_rankSpecial" is revised for the 7-choose-5 purpose.
The non-public first two and the seventh card are not available to view for other players until the very end


####TEXASHOLDEM#####

Similar to sevencardstud, it has multiple bettings. However, during the betting phases, we do not deal one card everytime.
We constructed the game thoroughly according to the guideline.
The two non public cards are not available to view for other players until the very end.




